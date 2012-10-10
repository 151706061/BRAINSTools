#ifndef __BRAINSFitSyN_h
#define __BRAINSFitSyN_h

#include "antsUtilities.h"
#include "itkantsRegistrationHelper.h"

typedef  ants::RegistrationHelper<3>                       SyNRegistrationHelperType;
typedef  SyNRegistrationHelperType::ImageType              ImageType;
typedef  SyNRegistrationHelperType::CompositeTransformType CompositeTransformType;

template <class FixedImageType, class MovingimageType>
typename CompositeTransformType::Pointer
simpleSynReg( typename FixedImageType::Pointer & fixedImage,
              typename MovingimageType::Pointer & movingImage,
              typename CompositeTransformType::Pointer compositeInitialTransform )
{
  typename SyNRegistrationHelperType::Pointer regHelper = SyNRegistrationHelperType::New();
    {
    const float lowerQuantile = 0.0;
    const float upperQuantile = 1.0;
    const bool  doWinsorize(false);
    regHelper->SetWinsorizeImageIntensities(doWinsorize, lowerQuantile, upperQuantile);
    }
    {
    const bool doHistogramMatch(true);
    regHelper->SetUseHistogramMatching(doHistogramMatch);
    }
    {
    const bool doEstimateLearningRateAtEachIteration = true;
    regHelper->SetDoEstimateLearningRateAtEachIteration( doEstimateLearningRateAtEachIteration );
    }
  // --convergence [250x100x70,1e-6,15]
    {
    std::vector<std::vector<unsigned int> > iterationList;
    std::vector<unsigned int>               iterations(3);
    iterations[0] = 350;
    iterations[1] = 200;
    iterations[2] = 5;   // NOTE: 5 does not converge, but it gives a reasonable result, 70 converges.
    iterationList.push_back(iterations);
    regHelper->SetIterations( iterationList );
    }
    {
    std::vector<double> convergenceThresholdList;
    const double        convergenceThreshold = 5e-6;
    convergenceThresholdList.push_back(convergenceThreshold);
    regHelper->SetConvergenceThresholds( convergenceThresholdList );
    }
    {
    std::vector<unsigned int> convergenceWindowSizeList;
    const unsigned int        convergenceWindowSize = 20;
    convergenceWindowSizeList.push_back(convergenceWindowSize);
    regHelper->SetConvergenceWindowSizes( convergenceWindowSizeList );
    }

    {
    // --shrink-factors 3x2x1
    std::vector<std::vector<unsigned int> > shrinkFactorsList;
    std::vector<unsigned int>               factors(3);
    factors[0] = 3;
    factors[1] = 2;
    factors[2] = 1;
    shrinkFactorsList.push_back(factors);
    regHelper->SetShrinkFactors( shrinkFactorsList );
    }
    {
    // --smoothing-sigmas 3x2x0
    std::vector<std::vector<float> > smoothingSigmasList;
    std::vector<float>               sigmas(3);
    sigmas[0] = 3;
    sigmas[1] = 2;
    sigmas[2] = 0;
    smoothingSigmasList.push_back(sigmas);
    regHelper->SetSmoothingSigmas( smoothingSigmasList );
    }

    {
    const std::string whichMetric = "cc";
    typename SyNRegistrationHelperType::MetricEnumeration curMetric = regHelper->StringToMetricType(whichMetric);
    const double weighting = 1.0;
    typename SyNRegistrationHelperType::SamplingStrategy samplingStrategy = SyNRegistrationHelperType::none; // none
    const unsigned int bins = 32;                                                                            // bins
    const unsigned int radius = 5;
    const double       samplingPercentage = 1.0;

    regHelper->AddMetric(curMetric, fixedImage, movingImage, weighting, samplingStrategy, bins, radius,
                         samplingPercentage);
    }
    {
    // --transform "SyN[0.33,3.0,0.0]"
    const float learningRate = 0.33;
    const float varianceForUpdateField = 3.0;
    const float varianceForTotalField = 0.0;
    regHelper->AddSyNTransform(learningRate, varianceForUpdateField, varianceForTotalField);
    }
  regHelper->SetMovingInitialTransform( compositeInitialTransform );
  regHelper->SetLogStream(std::cout);
  if( regHelper->DoRegistration() == EXIT_FAILURE )
    {
    ants::antscout << "FATAL ERROR: REGISTRATION PROCESS WAS UNSUCCESSFUL" << std::endl;
    }
  // Get the output transform
  typename CompositeTransformType::Pointer outputCompositeTransform = regHelper->GetCompositeTransform();
  // return composite result Transform;
  return outputCompositeTransform;
}

#endif
