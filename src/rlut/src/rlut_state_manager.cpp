#include "rlut_state_manager.hpp"

BaseState::BaseState(StateManager* mgr) : m_stateManager(mgr) {}

BaseState::~BaseState() {}

StateManager& BaseState::getStateManager() {
    return *m_stateManager;
}

void BaseState::setUpdateStatus(const bool flag) {
    m_canUpdate = flag;
}

void BaseState::setRenderStatus(const bool flag) {
    m_canRender = flag;
}

const bool BaseState::getUpdateStatus() const {
    return m_canUpdate;
}

const bool BaseState::getRenderStatus() const {
    return m_canRender;
}

void BaseState::disableState() {
    m_canUpdate = false;
    m_canRender = false;
}

void BaseState::enableState() {
    m_canUpdate = true;
    m_canRender = true;
}

StateManager::~StateManager() {
    clearStates();
}

void StateManager::pushState(const std::string& id) {
    StateItr it = getStateItr(id);
    if (it == m_states.end()) {
        StateData st;
        st.first = id;
        st.second.reset(m_factory.at(id)());
        m_states.emplace_back(std::move(st));
    }
    else {
        StateData st = std::move(*it);
        m_states.erase(it);
        m_states.emplace_back(std::move(st));
    }
    m_states.back().second->enableState();
}

void StateManager::popState(const std::string& id) {
    m_removals.emplace_back(id);
}

void StateManager::clearStates() {
    m_states.clear();
    m_factory.clear();
}

void StateManager::update() {
    if (!m_removals.empty()) {
        for (const std::string& id : m_removals) {
            StateItr it = getStateItr(id);
            if (it != m_states.end()) {
                m_states.erase(it);
            }
        }
        m_removals.clear();
    }
    for (int i = (int)m_states.size(); i > 0; --i) {
        const std::size_t idx = (std::size_t)(i - 1);
        if (m_states[idx].second->m_canUpdate) {
            m_states[idx].second->onUpdate();
        }
    }
}

void StateManager::render() {
    for (StateData& d : m_states) {
        if (d.second->m_canRender) {
            d.second->onRender();
        }
    }
}

void StateManager::setServiceLocator(void* locator) {
    m_serviceLocator = locator;
}

void StateManager::deregisterState(const std::string& id) {
    m_factory.erase(id);
}

StateManager::StateItr StateManager::getStateItr(const std::string& id) {
    return std::find_if(m_states.begin(), m_states.end(), [&](const StateData& d) { return id == d.first; });
}

