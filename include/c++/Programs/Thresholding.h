////////////////////////////////////////////////////////////////////////////////
//! @file	: Thresholding.h
//! @date   : Jul 2013
//!
//! @brief  : Image thresholding
//! 
//! Copyright (C) 2013 - CRVI
//!
//! This file is part of OpenCLIPP.
//! 
//! OpenCLIPP is free software: you can redistribute it and/or modify
//! it under the terms of the GNU Lesser General Public License version 3
//! as published by the Free Software Foundation.
//! 
//! OpenCLIPP is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU Lesser General Public License for more details.
//! 
//! You should have received a copy of the GNU Lesser General Public License
//! along with OpenCLIPP.  If not, see <http://www.gnu.org/licenses/>.
//! 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Program.h"

namespace OpenCLIPP
{

/// A program that does image thresholding
class CL_API Thresholding : public ImageProgram
{
public:
   Thresholding(COpenCL& CL)
   :  ImageProgram(CL, "Thresholding.cl")
   { }

   /// D = (S > Thresh ? valueHigher : S)
   void ThresholdGT(IImage& Source, IImage& Dest, float Thresh, float valueHigher = 255);

   /// D = (S < Thresh ? valueLower : S)
   void ThresholdLT(IImage& Source, IImage& Dest, float Thresh, float valueLower = 0);

   /// D = (S > Thresh ? valueHigher : (S < Thresh ? valueLower : S) )
   void ThresholdGTLT(IImage& Source, IImage& Dest, float threshLT, float valueLower, float threshGT, float valueHigher);

   enum ECompareOperation
   {
      LT,
      LQ,
      EQ,
      GQ,
      GT,
   };

   /// D = (S1 Op S2 ? S1 : S2)
   void Threshold(IImage& Source1, IImage& Source2, IImage& Dest, ECompareOperation Op = GT);

   /// D = (S Op V)  - D will be 0 or 255
   /// Dest must be a 8U image
   void Compare(IImage& Source, IImage& Dest, float Value, ECompareOperation Op = GT);

   /// D = (S1 Op S2) - D will be 0 or 255
   /// Dest must be a 8U image
   void Compare(IImage& Source1, IImage& Source2, IImage& Dest, ECompareOperation Op = GT);
};

}