////////////////////////////////////////////////////////////////////////////////
//! @file	: benchThresholdBase.hpp
//! @date   : Feb 2014
//!
//! @brief  : Base class for image thresholding
//! 
//! Copyright (C) 2014 - CRVI
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

#define CLASS_NAME CONCATENATE(CONCATENATE(BENCH_NAME,THRESHOLD_TYPE), Bench)
template<typename DataType> class CLASS_NAME;

typedef CLASS_NAME<unsigned char>   CONCATENATE(CONCATENATE(BENCH_NAME,THRESHOLD_TYPE), BenchU8);
typedef CLASS_NAME<unsigned short>  CONCATENATE(CONCATENATE(BENCH_NAME,THRESHOLD_TYPE), BenchU16);
typedef CLASS_NAME<float>           CONCATENATE(CONCATENATE(BENCH_NAME,THRESHOLD_TYPE), BenchF32);


template<typename DataType>
class CLASS_NAME : public BenchUnaryBase<DataType, THRESHOLD_USE_BUFFER>
{
public:
   void RunIPP();
   void RunNPP();
   void RunCL();

   bool HasCVTest()   const { return false; }
   bool HasCUDATest() const { return false; }
};

//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<unsigned char>::RunIPP()
{
   IPP_CODE(
         ippiThreshold_Val_8u_C1R( this->m_ImgSrc.Data(), this->m_ImgSrc.Step,
                             this->m_ImgDstIPP.Data(), this->m_ImgDstIPP.Step, 
                             this->m_IPPRoi, THRESH, 
                             CONCATENATE(VALUE,THRESHOLD_TYPE), GetIppCmpOp(THRESHOLD_TYPE));
      )
}
//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<unsigned short>::RunIPP()
{
   IPP_CODE(
         ippiThreshold_Val_16u_C1R( (Ipp16u*) this->m_ImgSrc.Data(), this->m_ImgSrc.Step,
                              (Ipp16u*) this->m_ImgDstIPP.Data(), this->m_ImgDstIPP.Step, 
                              this->m_IPPRoi, USHORT_THRESH, 
                              CONCATENATE(USHORT_VALUE,THRESHOLD_TYPE), GetIppCmpOp(THRESHOLD_TYPE));
      )
}
//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<float>::RunIPP()
{
   IPP_CODE(
         ippiThreshold_Val_32f_C1R( (Ipp32f*) this->m_ImgSrc.Data(), this->m_ImgSrc.Step,
                              (Ipp32f*) this->m_ImgDstIPP.Data(), this->m_ImgDstIPP.Step, 
                              this->m_IPPRoi, FLOAT_THRESH, 
                              CONCATENATE(FLOAT_VALUE,THRESHOLD_TYPE), GetIppCmpOp(THRESHOLD_TYPE));
      )
}

//-----------------------------------------------------------------------------------------------------------------------------
template<typename DataType>
void CLASS_NAME<DataType>::RunCL()
{
   float thresh = GetTreshold<DataType>();
   float value = GetTresholdValue<DataType>(THRESHOLD_TYPE);

   if (this->m_UsesBuffer)
      CONCATENATE(CONCATENATE(ocip, CONCATENATE(BENCH_NAME,THRESHOLD_TYPE)), _V)(this->m_CLBufferSrc, this->m_CLBufferDst, thresh, value);
   else
      CONCATENATE(ocip, CONCATENATE(BENCH_NAME,THRESHOLD_TYPE))(this->m_CLSrc, this->m_CLDst, thresh, value);
}

//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<unsigned char>::RunNPP()
{
   NPP_CODE(
         nppiThreshold_Val_8u_C1R( (Npp8u*) this->m_NPPSrc, this->m_NPPSrcStep,
                             (Npp8u*) this->m_NPPDst, this->m_NPPDstStep,
                             this->m_NPPRoi, THRESH, 
                             CONCATENATE(VALUE,THRESHOLD_TYPE), GetNppCmpOp(THRESHOLD_TYPE));
      )
}
//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<unsigned short>::RunNPP()
{
   NPP_CODE(
         nppiThreshold_Val_16u_C1R( (Ipp16u*) this->m_NPPSrc, this->m_NPPSrcStep,
                              (Ipp16u*) this->m_NPPDst, this->m_NPPDstStep,
                              this->m_NPPRoi, USHORT_THRESH, 
                              CONCATENATE(USHORT_VALUE,THRESHOLD_TYPE), GetNppCmpOp(THRESHOLD_TYPE));
      )
}
//-----------------------------------------------------------------------------------------------------------------------------
template<>
void CLASS_NAME<float>::RunNPP()
{
   NPP_CODE(
         nppiThreshold_Val_32f_C1R( (Ipp32f*) this->m_NPPSrc, this->m_NPPSrcStep,
                              (Ipp32f*) this->m_NPPDst, this->m_NPPDstStep,
                              this->m_NPPRoi, FLOAT_THRESH, 
                              CONCATENATE(FLOAT_VALUE,THRESHOLD_TYPE), GetNppCmpOp(THRESHOLD_TYPE));
      )
}


#undef CLASS_NAME
#undef THRESHOLD_TYPE
#undef BENCH_NAME
