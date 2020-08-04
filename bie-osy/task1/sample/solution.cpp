#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include "progtest_solver.h"
#include "sample_tester.h"

using namespace std;
#endif /* __PROGTEST__ */

class CSentinelHacker {
public:

	static bool SeqSolve(const vector<uint64_t> &fragments,
						 CBigInt &res);

	void AddTransmitter(ATransmitter x);

	void AddReceiver(AReceiver x);

	void AddFragment(uint64_t x);

	void Start(unsigned thrCount);

	void Stop(void);

private:
	static CBigInt result;

	atomic<unsigned> activeWorkers;
	atomic<unsigned> activeReceivers;

	vector<ATransmitter> m_transmitters;
	vector<AReceiver> m_receivers;
	vector<thread> m_workerThreads;
	vector<thread> m_receiverThreads;
	vector<thread> m_transmitterThreads;

	map<uint32_t, vector<uint64_t>> m_fragments;
	queue<pair<uint32_t, CBigInt>> m_messages;
	queue<uint64_t> buffer;

	mutex mtx_buffer;
	mutex mtx_messages;
	mutex mtx_fragments;

	condition_variable cv_BufferEmpty;
	condition_variable cv_fragmentsReady;

	void workerThread();

	void receiverThread(const AReceiver &r);

	void transmitterThread(const ATransmitter &t);

};
// TODO: CSentinelHacker implementation goes here

CBigInt CSentinelHacker::result = CBigInt(0);

bool CSentinelHacker::SeqSolve(const vector<uint64_t> &fragments, CBigInt &expressions) {

	uint32_t permutations = FindPermutations(fragments.data(), fragments.size(),
												  [](const uint8_t *fragments, size_t length) {
											 
													result = CountExpressions((fragments + 4), (length - 32));
											 										 
													});
	expressions = result;
	result = 0;
	return permutations > 0;
}

void CSentinelHacker::AddTransmitter(ATransmitter x) {
	m_transmitters.push_back(x);
}

void CSentinelHacker::AddReceiver(AReceiver x) {
	m_receivers.push_back(x);
}

void CSentinelHacker::Start(unsigned thrCount) {

	activeWorkers = thrCount;
	activeReceivers = m_receivers.size();

	for (size_t i = 0; i < m_receivers.size(); ++i) {
		m_receiverThreads.emplace_back(&CSentinelHacker::receiverThread, this, m_receivers[i]);
	}

	for (size_t i = 0; i < thrCount; ++i) {
		m_workerThreads.emplace_back(&CSentinelHacker::workerThread, this);
	}

	for (size_t i = 0; i < m_transmitters.size(); ++i) {
		m_transmitterThreads.emplace_back(&CSentinelHacker::transmitterThread, this, m_transmitters[i]);
	}
}

void CSentinelHacker::AddFragment(uint64_t x) {

	unique_lock<mutex> bufferLocker(mtx_buffer);
	buffer.push(x);
	bufferLocker.unlock();
	cv_BufferEmpty.notify_one();

}

void CSentinelHacker::receiverThread(const AReceiver &r) {

	uint64_t frag = 0;
	while (r->Recv(frag)) {
		unique_lock<mutex> bufferLocker(mtx_buffer);
		buffer.push(frag);
		bufferLocker.unlock();
		cv_BufferEmpty.notify_one();
	}
	activeReceivers--;
}


void CSentinelHacker::workerThread() {

	while (true) {

		unique_lock<mutex> bufferLocker(mtx_buffer);

		cv_BufferEmpty.wait(bufferLocker, [this]() {
			return !buffer.empty() || activeReceivers == 0;
		});


		if (buffer.empty() && activeReceivers == 0) {
			break;
		}

		auto data = buffer.front();
		buffer.pop();
		bufferLocker.unlock();
		
		
		unique_lock<mutex> fragmentsLocker(mtx_fragments);
		m_fragments[data >> 37].push_back(data);
		fragmentsLocker.unlock();
		
		CBigInt expressions = CBigInt(0);		

		uint32_t permutations = FindPermutations(m_fragments[data >> 37].data(), m_fragments[data >> 37].size(),
											 [&expressions](const uint8_t *fragments, size_t length) {
												expressions = CountExpressions(fragments + 4, length - 32);
											 });
											
		if (permutations) {
			
			unique_lock<mutex> messagesLocker(mtx_messages);
			m_messages.push(make_pair(data >> 37, expressions));
			messagesLocker.unlock();
			cv_fragmentsReady.notify_one();

			unique_lock<mutex> deleteLocker(mtx_fragments);
			m_fragments.erase((data >> 37));
			deleteLocker.unlock();
		}
	}

	activeWorkers--;
}

void CSentinelHacker::transmitterThread(const ATransmitter &t) {

	while (true) {
		unique_lock<mutex> messagesLocker(mtx_messages);
		cv_fragmentsReady.wait(messagesLocker, [this]() { return !m_messages.empty() || activeWorkers == 0; });

		if (m_messages.empty() && activeWorkers == 0) {
			break;
		}

		auto data = m_messages.front();
		m_messages.pop();                
		messagesLocker.unlock();
		
		t->Send(data.first, data.second);

	}
	
	for (auto &i : m_fragments)
		t->Incomplete(i.first);

}

void CSentinelHacker::Stop() {

	for (auto &receiver : m_receiverThreads) {
		receiver.join();
	}

	cv_BufferEmpty.notify_all();


	for (auto &worker : m_workerThreads) {
		worker.join();
	}

	cv_fragmentsReady.notify_all();


	for (auto &transmitter : m_transmitterThreads) {
		transmitter.join();
	}

}
//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__

int main() {
	using namespace std::placeholders;
	for (const auto &x : g_TestSets) {
		CBigInt res;
		assert (CSentinelHacker::SeqSolve(x.m_Fragments, res));
		assert (CBigInt(x.m_Result).CompareTo(res) == 0);
	}

	CSentinelHacker test;
	auto trans = make_shared<CExampleTransmitter>();
	AReceiver recv = make_shared<CExampleReceiver>(
			initializer_list<uint64_t>{0x02230000000c, 0x071e124dabef, 0x02360037680e, 0x071d2f8fe0a1, 0x055500150755});
			AReceiver recv1 = make_shared<CExampleReceiver>(
			initializer_list<uint64_t>{0x017f4cb42a68, 0x02260000000d, 0x072500000025});

	test.AddTransmitter(trans);
	test.AddReceiver(recv);
	test.AddReceiver(recv1);

	test.Start(3);

	static initializer_list<uint64_t> t1Data = {0x071f6b8342ab, 0x0738011f538d, 0x0732000129c3, 0x055e6ecfa0f9,
												0x02ffaa027451, 0x02280000010b, 0x02fb0b88bc3e};
	thread t1(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t1Data);

	static initializer_list<uint64_t> t2Data = {0x073700609bbd, 0x055901d61e7b, 0x022a0000032b, 0x016f0000edfb};
	thread t2(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t2Data);
	t1.join();
	t2.join();
	test.Stop();

	assert (trans->TotalSent() == 4);
	assert (trans->TotalIncomplete() == 2);
	return 0;
}

#endif /* __PROGTEST__ */
