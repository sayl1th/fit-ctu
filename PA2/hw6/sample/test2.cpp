#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */

class CComputer ...
class CNetwork ...
class CCPU ...
class CMemory ...
class CDisk ...

#ifndef __PROGTEST__
template<typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
  CNetwork n ( "FIT network" );
  n . AddComputer (
      CComputer ( "progtest.fit.cvut.cz" ) .
        AddAddress ( "147.32.232.142" ) .
        AddComponent ( CCPU ( 8, 2400 ) ) .
        AddComponent ( CCPU ( 8, 1200 ) ) .
        AddComponent ( CDisk ( CDisk::MAGNETIC, 1500 ) .
          AddPartition ( 50, "/" ) .
          AddPartition ( 5, "/boot" ).
          AddPartition ( 1000, "/var" ) ) .
        AddComponent ( CDisk ( CDisk::SSD, 60 ) .
          AddPartition ( 60, "/data" )  ) .
        AddComponent ( CMemory ( 2000 ) ).
        AddComponent ( CMemory ( 2000 ) ) ) .
    AddComputer (
      CComputer ( "edux.fit.cvut.cz" ) .
        AddAddress ( "147.32.232.158" ) .
        AddComponent ( CCPU ( 4, 1600 ) ) .
        AddComponent ( CMemory ( 4000 ) ).
        AddComponent ( CDisk ( CDisk::MAGNETIC, 2000 ) .
          AddPartition ( 100, "/" )   .
          AddPartition ( 1900, "/data" ) ) ) .
    AddComputer (
      CComputer ( "imap.fit.cvut.cz" ) .
        AddAddress ( "147.32.232.238" ) .
        AddComponent ( CCPU ( 4, 2500 ) ) .
        AddAddress ( "2001:718:2:2901::238" ) .
        AddComponent ( CMemory ( 8000 ) ) );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "\\-Host: imap.fit.cvut.cz\n"
    "  +-147.32.232.238\n"
    "  +-2001:718:2:2901::238\n"
    "  +-CPU, 4 cores @ 2500MHz\n"
    "  \\-Memory, 8000 MiB\n" );
  CNetwork x = n;
  auto c = x . FindComputer ( "imap.fit.cvut.cz" );
  assert ( toString ( *c ) ==
    "Host: imap.fit.cvut.cz\n"
    "+-147.32.232.238\n"
    "+-2001:718:2:2901::238\n"
    "+-CPU, 4 cores @ 2500MHz\n"
    "\\-Memory, 8000 MiB\n" );
  c -> AddComponent ( CDisk ( CDisk::MAGNETIC, 1000 ) .
            AddPartition ( 100, "system" ) .
            AddPartition ( 200, "WWW" ) .
            AddPartition ( 700, "mail" ) );
  assert ( toString ( x ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "\\-Host: imap.fit.cvut.cz\n"
    "  +-147.32.232.238\n"
    "  +-2001:718:2:2901::238\n"
    "  +-CPU, 4 cores @ 2500MHz\n"
    "  +-Memory, 8000 MiB\n"
    "  \\-HDD, 1000 GiB\n"
    "    +-[0]: 100 GiB, system\n"
    "    +-[1]: 200 GiB, WWW\n"
    "    \\-[2]: 700 GiB, mail\n" );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "\\-Host: imap.fit.cvut.cz\n"
    "  +-147.32.232.238\n"
    "  +-2001:718:2:2901::238\n"
    "  +-CPU, 4 cores @ 2500MHz\n"
    "  \\-Memory, 8000 MiB\n" );
  n . AddComputer ( CComputer ( "vm01.fit.cvut.cz" ) .
    AddAddress ( "147.32.232.232" ) .
      AddComponent ( CCPU ( 32, 4000 ) ) .
      AddComponent ( CMemory ( 32768 ) ) .
      AddComponent ( CDisk ( CDisk::MAGNETIC, 3000 ) .
        AddPartition ( 500, "SYSTEM" ) .
        AddPartition ( 2000, "DATA" ) .
        AddPartition ( 500, "BACKUP" ) ) .
      AddComponent ( CNetwork ( "dummy00" ) .
        AddComputer ( CComputer ( "testing.fit.cvut.cz" ) .
          AddAddress ( "192.168.1.1" ) .
          AddComponent ( CCPU ( 1, 300 ) ) .
          AddComponent ( CMemory ( 256 ) ) ) ) .
      AddComponent ( CMemory ( 16384 ) ) .
      AddComponent ( CNetwork ( "vnet00" ) ) );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "+-Host: imap.fit.cvut.cz\n"
    "| +-147.32.232.238\n"
    "| +-2001:718:2:2901::238\n"
    "| +-CPU, 4 cores @ 2500MHz\n"
    "| \\-Memory, 8000 MiB\n"
    "\\-Host: vm01.fit.cvut.cz\n"
    "  +-147.32.232.232\n"
    "  +-CPU, 32 cores @ 4000MHz\n"
    "  +-Memory, 32768 MiB\n"
    "  +-HDD, 3000 GiB\n"
    "  | +-[0]: 500 GiB, SYSTEM\n"
    "  | +-[1]: 2000 GiB, DATA\n"
    "  | \\-[2]: 500 GiB, BACKUP\n"
    "  +-Network: dummy00\n"
    "  | \\-Host: testing.fit.cvut.cz\n"
    "  |   +-192.168.1.1\n"
    "  |   +-CPU, 1 cores @ 300MHz\n"
    "  |   \\-Memory, 256 MiB\n"
    "  +-Memory, 16384 MiB\n"
    "  \\-Network: vnet00\n" );
  auto vmnet = n . FindNetwork ( "vnet00" );
  vmnet -> AddComputer ( CComputer ( "monitor1.fit.cvut.cz" ) .
    AddAddress ( "147.32.232.254" ) .
    AddComponent ( CCPU ( 2, 1500 ) ) .
    AddComponent ( CMemory ( 4096 ) ) .
    AddComponent ( CDisk ( CDisk::MAGNETIC, 750 ) .
      AddPartition ( 100, "root" ) .
      AddPartition ( 600, "log" ) ) );
  assert ( toString ( *vmnet ) ==
    "Network: vnet00\n"
    "\\-Host: monitor1.fit.cvut.cz\n"
    "  +-147.32.232.254\n"
    "  +-CPU, 2 cores @ 1500MHz\n"
    "  +-Memory, 4096 MiB\n"
    "  \\-HDD, 750 GiB\n"
    "    +-[0]: 100 GiB, root\n"
    "    \\-[1]: 600 GiB, log\n" );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "+-Host: imap.fit.cvut.cz\n"
    "| +-147.32.232.238\n"
    "| +-2001:718:2:2901::238\n"
    "| +-CPU, 4 cores @ 2500MHz\n"
    "| \\-Memory, 8000 MiB\n"
    "\\-Host: vm01.fit.cvut.cz\n"
    "  +-147.32.232.232\n"
    "  +-CPU, 32 cores @ 4000MHz\n"
    "  +-Memory, 32768 MiB\n"
    "  +-HDD, 3000 GiB\n"
    "  | +-[0]: 500 GiB, SYSTEM\n"
    "  | +-[1]: 2000 GiB, DATA\n"
    "  | \\-[2]: 500 GiB, BACKUP\n"
    "  +-Network: dummy00\n"
    "  | \\-Host: testing.fit.cvut.cz\n"
    "  |   +-192.168.1.1\n"
    "  |   +-CPU, 1 cores @ 300MHz\n"
    "  |   \\-Memory, 256 MiB\n"
    "  +-Memory, 16384 MiB\n"
    "  \\-Network: vnet00\n"
    "    \\-Host: monitor1.fit.cvut.cz\n"
    "      +-147.32.232.254\n"
    "      +-CPU, 2 cores @ 1500MHz\n"
    "      +-Memory, 4096 MiB\n"
    "      \\-HDD, 750 GiB\n"
    "        +-[0]: 100 GiB, root\n"
    "        \\-[1]: 600 GiB, log\n" );
  vmnet -> AddComputer ( n . FindComputer ( "monitor1.fit.cvut.cz" )
           -> Duplicate ( { pair<string,string>("monitor1.fit.cvut.cz","monitor2.fit.cvut.cz") } ) );
  assert ( toString ( *vmnet ) ==
    "Network: vnet00\n"
    "+-Host: monitor1.fit.cvut.cz\n"
    "| +-147.32.232.254\n"
    "| +-CPU, 2 cores @ 1500MHz\n"
    "| +-Memory, 4096 MiB\n"
    "| \\-HDD, 750 GiB\n"
    "|   +-[0]: 100 GiB, root\n"
    "|   \\-[1]: 600 GiB, log\n"
    "\\-Host: monitor2.fit.cvut.cz\n"
    "  +-147.32.232.254\n"
    "  +-CPU, 2 cores @ 1500MHz\n"
    "  +-Memory, 4096 MiB\n"
    "  \\-HDD, 750 GiB\n"
    "    +-[0]: 100 GiB, root\n"
    "    \\-[1]: 600 GiB, log\n" );
  n . AddComputer ( n . FindComputer ( "vm01.fit.cvut.cz" )
        -> Duplicate (
             {
               pair<string,string>("monitor1.fit.cvut.cz","monitor3.fit.cvut.cz"),
               pair<string,string>("monitor2.fit.cvut.cz","monitor4.fit.cvut.cz"),
               pair<string,string>("vm01.fit.cvut.cz","vm02.fit.cvut.cz")
             } ) );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "+-Host: imap.fit.cvut.cz\n"
    "| +-147.32.232.238\n"
    "| +-2001:718:2:2901::238\n"
    "| +-CPU, 4 cores @ 2500MHz\n"
    "| \\-Memory, 8000 MiB\n"
    "+-Host: vm01.fit.cvut.cz\n"
    "| +-147.32.232.232\n"
    "| +-CPU, 32 cores @ 4000MHz\n"
    "| +-Memory, 32768 MiB\n"
    "| +-HDD, 3000 GiB\n"
    "| | +-[0]: 500 GiB, SYSTEM\n"
    "| | +-[1]: 2000 GiB, DATA\n"
    "| | \\-[2]: 500 GiB, BACKUP\n"
    "| +-Network: dummy00\n"
    "| | \\-Host: testing.fit.cvut.cz\n"
    "| |   +-192.168.1.1\n"
    "| |   +-CPU, 1 cores @ 300MHz\n"
    "| |   \\-Memory, 256 MiB\n"
    "| +-Memory, 16384 MiB\n"
    "| \\-Network: vnet00\n"
    "|   +-Host: monitor1.fit.cvut.cz\n"
    "|   | +-147.32.232.254\n"
    "|   | +-CPU, 2 cores @ 1500MHz\n"
    "|   | +-Memory, 4096 MiB\n"
    "|   | \\-HDD, 750 GiB\n"
    "|   |   +-[0]: 100 GiB, root\n"
    "|   |   \\-[1]: 600 GiB, log\n"
    "|   \\-Host: monitor2.fit.cvut.cz\n"
    "|     +-147.32.232.254\n"
    "|     +-CPU, 2 cores @ 1500MHz\n"
    "|     +-Memory, 4096 MiB\n"
    "|     \\-HDD, 750 GiB\n"
    "|       +-[0]: 100 GiB, root\n"
    "|       \\-[1]: 600 GiB, log\n"
    "\\-Host: vm02.fit.cvut.cz\n"
    "  +-147.32.232.232\n"
    "  +-CPU, 32 cores @ 4000MHz\n"
    "  +-Memory, 32768 MiB\n"
    "  +-HDD, 3000 GiB\n"
    "  | +-[0]: 500 GiB, SYSTEM\n"
    "  | +-[1]: 2000 GiB, DATA\n"
    "  | \\-[2]: 500 GiB, BACKUP\n"
    "  +-Network: dummy00\n"
    "  | \\-Host: testing.fit.cvut.cz\n"
    "  |   +-192.168.1.1\n"
    "  |   +-CPU, 1 cores @ 300MHz\n"
    "  |   \\-Memory, 256 MiB\n"
    "  +-Memory, 16384 MiB\n"
    "  \\-Network: vnet00\n"
    "    +-Host: monitor3.fit.cvut.cz\n"
    "    | +-147.32.232.254\n"
    "    | +-CPU, 2 cores @ 1500MHz\n"
    "    | +-Memory, 4096 MiB\n"
    "    | \\-HDD, 750 GiB\n"
    "    |   +-[0]: 100 GiB, root\n"
    "    |   \\-[1]: 600 GiB, log\n"
    "    \\-Host: monitor4.fit.cvut.cz\n"
    "      +-147.32.232.254\n"
    "      +-CPU, 2 cores @ 1500MHz\n"
    "      +-Memory, 4096 MiB\n"
    "      \\-HDD, 750 GiB\n"
    "        +-[0]: 100 GiB, root\n"
    "        \\-[1]: 600 GiB, log\n" );
  vmnet -> AddComputer ( n . FindComputer ( "vm02.fit.cvut.cz" )
           -> Duplicate (
                {
                  pair<string,string>("monitor3.fit.cvut.cz","monitor5.fit.cvut.cz"),
                  pair<string,string>("monitor4.fit.cvut.cz","monitor6.fit.cvut.cz"),
                  pair<string,string>("vm02.fit.cvut.cz","vm03.fit.cvut.cz"),
                  pair<string,string>("vnet00","vnet01")
                } ) );
  assert ( toString ( *vmnet ) ==
    "Network: vnet00\n"
    "+-Host: monitor1.fit.cvut.cz\n"
    "| +-147.32.232.254\n"
    "| +-CPU, 2 cores @ 1500MHz\n"
    "| +-Memory, 4096 MiB\n"
    "| \\-HDD, 750 GiB\n"
    "|   +-[0]: 100 GiB, root\n"
    "|   \\-[1]: 600 GiB, log\n"
    "+-Host: monitor2.fit.cvut.cz\n"
    "| +-147.32.232.254\n"
    "| +-CPU, 2 cores @ 1500MHz\n"
    "| +-Memory, 4096 MiB\n"
    "| \\-HDD, 750 GiB\n"
    "|   +-[0]: 100 GiB, root\n"
    "|   \\-[1]: 600 GiB, log\n"
    "\\-Host: vm03.fit.cvut.cz\n"
    "  +-147.32.232.232\n"
    "  +-CPU, 32 cores @ 4000MHz\n"
    "  +-Memory, 32768 MiB\n"
    "  +-HDD, 3000 GiB\n"
    "  | +-[0]: 500 GiB, SYSTEM\n"
    "  | +-[1]: 2000 GiB, DATA\n"
    "  | \\-[2]: 500 GiB, BACKUP\n"
    "  +-Network: dummy00\n"
    "  | \\-Host: testing.fit.cvut.cz\n"
    "  |   +-192.168.1.1\n"
    "  |   +-CPU, 1 cores @ 300MHz\n"
    "  |   \\-Memory, 256 MiB\n"
    "  +-Memory, 16384 MiB\n"
    "  \\-Network: vnet01\n"
    "    +-Host: monitor5.fit.cvut.cz\n"
    "    | +-147.32.232.254\n"
    "    | +-CPU, 2 cores @ 1500MHz\n"
    "    | +-Memory, 4096 MiB\n"
    "    | \\-HDD, 750 GiB\n"
    "    |   +-[0]: 100 GiB, root\n"
    "    |   \\-[1]: 600 GiB, log\n"
    "    \\-Host: monitor6.fit.cvut.cz\n"
    "      +-147.32.232.254\n"
    "      +-CPU, 2 cores @ 1500MHz\n"
    "      +-Memory, 4096 MiB\n"
    "      \\-HDD, 750 GiB\n"
    "        +-[0]: 100 GiB, root\n"
    "        \\-[1]: 600 GiB, log\n" );
  n . FindComputer ( "vm02.fit.cvut.cz" )
      -> FindNetwork ( "vnet00" )
      -> AddComputer ( n . FindComputer ( "vm01.fit.cvut.cz" )
           -> Duplicate (
                {
                  pair<string,string>("monitor1.fit.cvut.cz","monitor11.fit.cvut.cz"),
                  pair<string,string>("monitor2.fit.cvut.cz","monitor12.fit.cvut.cz"),
                  pair<string,string>("vm01.fit.cvut.cz","vm11.fit.cvut.cz"),
                  pair<string,string>("vm03.fit.cvut.cz","vm13.fit.cvut.cz"),
                  pair<string,string>("vnet00","vnet10"),
                  pair<string,string>("vnet01","vnet11")
                } ) );
  assert ( toString ( n ) ==
    "Network: FIT network\n"
    "+-Host: progtest.fit.cvut.cz\n"
    "| +-147.32.232.142\n"
    "| +-CPU, 8 cores @ 2400MHz\n"
    "| +-CPU, 8 cores @ 1200MHz\n"
    "| +-HDD, 1500 GiB\n"
    "| | +-[0]: 50 GiB, /\n"
    "| | +-[1]: 5 GiB, /boot\n"
    "| | \\-[2]: 1000 GiB, /var\n"
    "| +-SSD, 60 GiB\n"
    "| | \\-[0]: 60 GiB, /data\n"
    "| +-Memory, 2000 MiB\n"
    "| \\-Memory, 2000 MiB\n"
    "+-Host: edux.fit.cvut.cz\n"
    "| +-147.32.232.158\n"
    "| +-CPU, 4 cores @ 1600MHz\n"
    "| +-Memory, 4000 MiB\n"
    "| \\-HDD, 2000 GiB\n"
    "|   +-[0]: 100 GiB, /\n"
    "|   \\-[1]: 1900 GiB, /data\n"
    "+-Host: imap.fit.cvut.cz\n"
    "| +-147.32.232.238\n"
    "| +-2001:718:2:2901::238\n"
    "| +-CPU, 4 cores @ 2500MHz\n"
    "| \\-Memory, 8000 MiB\n"
    "+-Host: vm01.fit.cvut.cz\n"
    "| +-147.32.232.232\n"
    "| +-CPU, 32 cores @ 4000MHz\n"
    "| +-Memory, 32768 MiB\n"
    "| +-HDD, 3000 GiB\n"
    "| | +-[0]: 500 GiB, SYSTEM\n"
    "| | +-[1]: 2000 GiB, DATA\n"
    "| | \\-[2]: 500 GiB, BACKUP\n"
    "| +-Network: dummy00\n"
    "| | \\-Host: testing.fit.cvut.cz\n"
    "| |   +-192.168.1.1\n"
    "| |   +-CPU, 1 cores @ 300MHz\n"
    "| |   \\-Memory, 256 MiB\n"
    "| +-Memory, 16384 MiB\n"
    "| \\-Network: vnet00\n"
    "|   +-Host: monitor1.fit.cvut.cz\n"
    "|   | +-147.32.232.254\n"
    "|   | +-CPU, 2 cores @ 1500MHz\n"
    "|   | +-Memory, 4096 MiB\n"
    "|   | \\-HDD, 750 GiB\n"
    "|   |   +-[0]: 100 GiB, root\n"
    "|   |   \\-[1]: 600 GiB, log\n"
    "|   +-Host: monitor2.fit.cvut.cz\n"
    "|   | +-147.32.232.254\n"
    "|   | +-CPU, 2 cores @ 1500MHz\n"
    "|   | +-Memory, 4096 MiB\n"
    "|   | \\-HDD, 750 GiB\n"
    "|   |   +-[0]: 100 GiB, root\n"
    "|   |   \\-[1]: 600 GiB, log\n"
    "|   \\-Host: vm03.fit.cvut.cz\n"
    "|     +-147.32.232.232\n"
    "|     +-CPU, 32 cores @ 4000MHz\n"
    "|     +-Memory, 32768 MiB\n"
    "|     +-HDD, 3000 GiB\n"
    "|     | +-[0]: 500 GiB, SYSTEM\n"
    "|     | +-[1]: 2000 GiB, DATA\n"
    "|     | \\-[2]: 500 GiB, BACKUP\n"
    "|     +-Network: dummy00\n"
    "|     | \\-Host: testing.fit.cvut.cz\n"
    "|     |   +-192.168.1.1\n"
    "|     |   +-CPU, 1 cores @ 300MHz\n"
    "|     |   \\-Memory, 256 MiB\n"
    "|     +-Memory, 16384 MiB\n"
    "|     \\-Network: vnet01\n"
    "|       +-Host: monitor5.fit.cvut.cz\n"
    "|       | +-147.32.232.254\n"
    "|       | +-CPU, 2 cores @ 1500MHz\n"
    "|       | +-Memory, 4096 MiB\n"
    "|       | \\-HDD, 750 GiB\n"
    "|       |   +-[0]: 100 GiB, root\n"
    "|       |   \\-[1]: 600 GiB, log\n"
    "|       \\-Host: monitor6.fit.cvut.cz\n"
    "|         +-147.32.232.254\n"
    "|         +-CPU, 2 cores @ 1500MHz\n"
    "|         +-Memory, 4096 MiB\n"
    "|         \\-HDD, 750 GiB\n"
    "|           +-[0]: 100 GiB, root\n"
    "|           \\-[1]: 600 GiB, log\n"
    "\\-Host: vm02.fit.cvut.cz\n"
    "  +-147.32.232.232\n"
    "  +-CPU, 32 cores @ 4000MHz\n"
    "  +-Memory, 32768 MiB\n"
    "  +-HDD, 3000 GiB\n"
    "  | +-[0]: 500 GiB, SYSTEM\n"
    "  | +-[1]: 2000 GiB, DATA\n"
    "  | \\-[2]: 500 GiB, BACKUP\n"
    "  +-Network: dummy00\n"
    "  | \\-Host: testing.fit.cvut.cz\n"
    "  |   +-192.168.1.1\n"
    "  |   +-CPU, 1 cores @ 300MHz\n"
    "  |   \\-Memory, 256 MiB\n"
    "  +-Memory, 16384 MiB\n"
    "  \\-Network: vnet00\n"
    "    +-Host: monitor3.fit.cvut.cz\n"
    "    | +-147.32.232.254\n"
    "    | +-CPU, 2 cores @ 1500MHz\n"
    "    | +-Memory, 4096 MiB\n"
    "    | \\-HDD, 750 GiB\n"
    "    |   +-[0]: 100 GiB, root\n"
    "    |   \\-[1]: 600 GiB, log\n"
    "    +-Host: monitor4.fit.cvut.cz\n"
    "    | +-147.32.232.254\n"
    "    | +-CPU, 2 cores @ 1500MHz\n"
    "    | +-Memory, 4096 MiB\n"
    "    | \\-HDD, 750 GiB\n"
    "    |   +-[0]: 100 GiB, root\n"
    "    |   \\-[1]: 600 GiB, log\n"
    "    \\-Host: vm11.fit.cvut.cz\n"
    "      +-147.32.232.232\n"
    "      +-CPU, 32 cores @ 4000MHz\n"
    "      +-Memory, 32768 MiB\n"
    "      +-HDD, 3000 GiB\n"
    "      | +-[0]: 500 GiB, SYSTEM\n"
    "      | +-[1]: 2000 GiB, DATA\n"
    "      | \\-[2]: 500 GiB, BACKUP\n"
    "      +-Network: dummy00\n"
    "      | \\-Host: testing.fit.cvut.cz\n"
    "      |   +-192.168.1.1\n"
    "      |   +-CPU, 1 cores @ 300MHz\n"
    "      |   \\-Memory, 256 MiB\n"
    "      +-Memory, 16384 MiB\n"
    "      \\-Network: vnet10\n"
    "        +-Host: monitor11.fit.cvut.cz\n"
    "        | +-147.32.232.254\n"
    "        | +-CPU, 2 cores @ 1500MHz\n"
    "        | +-Memory, 4096 MiB\n"
    "        | \\-HDD, 750 GiB\n"
    "        |   +-[0]: 100 GiB, root\n"
    "        |   \\-[1]: 600 GiB, log\n"
    "        +-Host: monitor12.fit.cvut.cz\n"
    "        | +-147.32.232.254\n"
    "        | +-CPU, 2 cores @ 1500MHz\n"
    "        | +-Memory, 4096 MiB\n"
    "        | \\-HDD, 750 GiB\n"
    "        |   +-[0]: 100 GiB, root\n"
    "        |   \\-[1]: 600 GiB, log\n"
    "        \\-Host: vm13.fit.cvut.cz\n"
    "          +-147.32.232.232\n"
    "          +-CPU, 32 cores @ 4000MHz\n"
    "          +-Memory, 32768 MiB\n"
    "          +-HDD, 3000 GiB\n"
    "          | +-[0]: 500 GiB, SYSTEM\n"
    "          | +-[1]: 2000 GiB, DATA\n"
    "          | \\-[2]: 500 GiB, BACKUP\n"
    "          +-Network: dummy00\n"
    "          | \\-Host: testing.fit.cvut.cz\n"
    "          |   +-192.168.1.1\n"
    "          |   +-CPU, 1 cores @ 300MHz\n"
    "          |   \\-Memory, 256 MiB\n"
    "          +-Memory, 16384 MiB\n"
    "          \\-Network: vnet11\n"
    "            +-Host: monitor5.fit.cvut.cz\n"
    "            | +-147.32.232.254\n"
    "            | +-CPU, 2 cores @ 1500MHz\n"
    "            | +-Memory, 4096 MiB\n"
    "            | \\-HDD, 750 GiB\n"
    "            |   +-[0]: 100 GiB, root\n"
    "            |   \\-[1]: 600 GiB, log\n"
    "            \\-Host: monitor6.fit.cvut.cz\n"
    "              +-147.32.232.254\n"
    "              +-CPU, 2 cores @ 1500MHz\n"
    "              +-Memory, 4096 MiB\n"
    "              \\-HDD, 750 GiB\n"
    "                +-[0]: 100 GiB, root\n"
    "                \\-[1]: 600 GiB, log\n" );
  return 0;
}
#endif /* __PROGTEST__ */
