#pragma once

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <utility>

class StateManager;

class BaseState {
public:

    friend class StateManager;

public:

    BaseState(StateManager* mgr);
    virtual ~BaseState();

    virtual void onUpdate() = 0;
    virtual void onRender() = 0;

    StateManager& getStateManager();

    // NOTE:
    // in a future project remove the functions below and delgate them to the state manager class

    void setUpdateStatus(const bool flag);
    void setRenderStatus(const bool flag);

    const bool getUpdateStatus() const;
    const bool getRenderStatus() const;

    void disableState();
    void enableState();

private:
    StateManager* m_stateManager = nullptr;
    bool m_canUpdate = true;
    bool m_canRender = true;
};

class StateManager {
public:

    StateManager() = default;
    ~StateManager();

    void pushState(const std::string& id);
    void popState(const std::string& id);
    void clearStates();

    template <class D>
    D& getState(const std::string& id) {
        return *static_cast<D*>(getStateItr(id)->second.get());
    }

    void update();
    void render();

    void setServiceLocator(void* locator);

    template <class L>
    L& getServiceLocator() {
        return *static_cast<L*>(m_serviceLocator);
    }

    // NOTE:
    // this uses C++20 perfect capture
    template <class D, class ...A>
    bool registerState(const std::string& id, A&& ...args) {
        return m_factory.try_emplace(id, [this, ... args = std::forward<A>(args)]() -> D* { return new D(this, args...); }).second;
    }

    void deregisterState(const std::string& id);

private:

    using StateData = std::pair<std::string, std::unique_ptr<BaseState>>;
    using StateItr = std::vector<StateData>::iterator;

private:

    StateItr getStateItr(const std::string& id);

private:
    std::vector<StateData> m_states;
    std::vector<std::string> m_removals;
    std::unordered_map<std::string, std::function<BaseState*()>> m_factory;
    void* m_serviceLocator = nullptr;
};
