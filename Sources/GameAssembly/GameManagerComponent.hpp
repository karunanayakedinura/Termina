#pragma once

#include <Termina/Scripting/API/ScriptingAPI.hpp>

using namespace TerminaScript;

class GameManagerComponent : public ScriptableComponent
{
public:
    GameManagerComponent(); 
    GameManagerComponent(Termina::Actor* owner); 

    void Update(float dt) override;
    void Stop() override;

    static GameManagerComponent* Instance;

    bool IsGameOver() const { return m_GameOver; }
    bool HasWon() const { return m_Win; }

    void TriggerWin();
    void TriggerLose();
 

private:
    bool m_GameOver = false;
    bool m_Win = false;
};