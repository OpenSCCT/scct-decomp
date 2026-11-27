#include "versus_mgm_timed_key.h"

#pragma optimize("", off)
INT MgmChild::FindKey(FLOAT Seconds, INT MillisecondsPerFrame) const
{
    INT Result = -1;
    FLOAT KeyTime;
    for (unsigned int Index = 0; Index < Keys.size(); ++Index) {
        KeyTime = Keys[Index]->GetFrame() * MillisecondsPerFrame / 1000.f;
        if (KeyTime > Seconds) {
            Result = Index - 1;
            break;
        }
        Result = Index;
    }
    return Result;
}

#pragma optimize("", on)

void MgmChild::EvaluateTime(FLOAT Seconds, INT MillisecondsPerFrame, BYTE Update)
{
    if (Keys.size()) {
        const INT PreviousKey = CurrentKey;
        CurrentKey = FindKey(Seconds, MillisecondsPerFrame);
        if (CurrentKey != -1) {
            if (CurrentKey != Keys.size() - 1 && Keys[CurrentKey + 1]->Interpolation) {
                MgmKeyInterpolation Blend;
                FLOAT FromTime = Keys[CurrentKey]->GetFrame() * MillisecondsPerFrame / 1000.f;
                FLOAT ToTime = Keys[CurrentKey + 1]->GetFrame() * MillisecondsPerFrame / 1000.f;
                Blend.From = Keys[CurrentKey]->Value;
                Blend.To = Keys[CurrentKey + 1]->Value;
                Blend.Elapsed = (Seconds - FromTime);
                Blend.Duration = (ToTime - FromTime);
                Blend.Mode = Keys[CurrentKey + 1]->Interpolation;
                Blend.unk_0c = 1;
                Content->Keyframe->Interpolate(Blend);
            } else {
                Content->Keyframe->CopyFrom(*Keys[CurrentKey]->Value);
            }
            const INT EventKey = CurrentKey;
            if (PreviousKey != EventKey && Update) {
                for (unsigned int i = 0; i < Keys[EventKey]->Actions.size(); ++i)
                    Keys[EventKey]->Actions[i]->Execute();
            }
        }
    }
}
