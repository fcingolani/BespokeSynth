/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  FMSynth.h
//  modularSynth
//
//  Created by Ryan Challinor on 1/6/13.
//
//

#ifndef __modularSynth__FMSynth__
#define __modularSynth__FMSynth__

#include <iostream>
#include "IAudioSource.h"
#include "PolyphonyMgr.h"
#include "FMVoice.h"
#include "ADSR.h"
#include "INoteReceiver.h"
#include "IDrawableModule.h"
#include "Slider.h"
#include "DropdownList.h"
#include "ADSRDisplay.h"

class FMSynth : public IAudioSource, public INoteReceiver, public IDrawableModule, public IDropdownListener, public IFloatSliderListener
{
public:
   FMSynth();
   ~FMSynth();
   static IDrawableModule* Create() { return new FMSynth(); }
   
   
   void CreateUIControls() override;

   //IAudioSource
   void Process(double time) override;
   void SetEnabled(bool enabled) override;

   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   void SendCC(int control, int value, int voiceIdx = -1) override {}

   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void CheckboxUpdated(Checkbox* checkbox) override;

   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;

   bool HasDebugDraw() const override { return true; }
   
private:
   void UpdateHarmonicRatio();

   //IDrawableModule
   void DrawModule() override;
   void DrawModuleUnclipped() override;
   void GetModuleDimensions(float& width, float& height) override { width = 180; height = 203; }
   bool Enabled() const override { return mEnabled; }
   
   PolyphonyMgr mPolyMgr;
   NoteInputBuffer mNoteInputBuffer;
   FMVoiceParams mVoiceParams;
   FloatSlider* mVolSlider;
   ADSRDisplay* mAdsrDisplayVol;
   FloatSlider* mPhaseOffsetSlider0;
   
   FloatSlider* mHarmSlider;
   ADSRDisplay* mAdsrDisplayHarm;
   FloatSlider* mModSlider;
   ADSRDisplay* mAdsrDisplayMod;
   int mHarmRatioBase;  //negative means 1/val
   float mHarmRatioTweak;
   DropdownList* mHarmRatioBaseDropdown;
   FloatSlider* mPhaseOffsetSlider1;
   
   FloatSlider* mHarmSlider2;
   ADSRDisplay* mAdsrDisplayHarm2;
   FloatSlider* mModSlider2;
   ADSRDisplay* mAdsrDisplayMod2;
   int mHarmRatioBase2;  //negative means 1/val
   float mHarmRatioTweak2;
   DropdownList* mHarmRatioBaseDropdown2;
   FloatSlider* mPhaseOffsetSlider2;

   ChannelBuffer mWriteBuffer;

   std::string mDebugLines;
};

#endif /* defined(__modularSynth__FMSynth__) */

