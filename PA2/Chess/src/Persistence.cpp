//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Persistence.hpp"

Persistence::Persistence() : m_gameSession(nullptr) {}

Persistence::Persistence(GameSession* session) : m_gameSession(session) {}

Persistence::~Persistence()  = default;
