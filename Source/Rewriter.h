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
//  Rewriter.h
//  modularSynth
//
//  Created by Ryan Challinor on 3/16/13.
//
//

#ifndef __modularSynth__Rewriter__
#define __modularSynth__Rewriter__

#include <iostream>
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "ClickButton.h"
#include "RollingBuffer.h"
#include "MidiDevice.h"
#include "Checkbox.h"

class Looper;

class Rewriter : public IAudioProcessor, public IDrawableModule, public IButtonListener
{
public:
   Rewriter();
   virtual ~Rewriter();
   static IDrawableModule* Create() { return new Rewriter(); }
   
   
   void CreateUIControls() override;

   void Go();
   
   void PostRepatch(PatchCableSource* cableSource, bool fromUserClick) override;

   //IAudioSource
   void Process(double time) override;

   //IButtonListener
   void ButtonClicked(ClickButton* button) override;
   
   void CheckboxUpdated(Checkbox* checkbox) override;
   
   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SaveLayout(ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& w, float& h) override { w=mWidth; h=mHeight; }
   bool Enabled() const override { return mEnabled; }
   
   float mWidth;
   float mHeight;

   double mStartRecordTime;

   ClickButton* mRewriteButton;
   ClickButton* mStartRecordTimeButton;

   RollingBuffer mRecordBuffer;
   Looper* mConnectedLooper;
   
   PatchCableSource* mLooperCable;
};


#endif /* defined(__modularSynth__Rewriter__) */

