#pragma once

#include "core/core.h"
#include "core/game/finite_state_machine.h"

enum struct EPlayerStates{
    Idle,
    Running
    //Jumping
};


struct FSMPlayerController : public FSM<EPlayerStates>{
    DEFINE_STATE(FSMPlayerController, EPlayerStates, Idle);
    DEFINE_STATE(FSMPlayerController, EPlayerStates, Running);
    //DEFINE_STATE(FSMPlayerController, EPlayerStates, Jumping);


    FSMPlayerController(){
        CONNECT_STATE(EPlayerStates, Idle);
        CONNECT_STATE(EPlayerStates, Running);
        //CONNECT_STATE(EPlayerStates, Jumping);
    }
};