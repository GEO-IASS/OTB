/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.

  Some parts of this code are derived from ITK. See ITKCopyright.txt
  for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbStreamingVectorizedSegmentationOGR_h
#define __otbStreamingVectorizedSegmentationOGR_h

#include "itkExtractImageFilter.h"

#include "otbPersistentImageFilter.h"
#include "otbPersistentFilterStreamingDecorator.h"
#include "otbPersistentImageToOGRDataFilter.h"
#include "otbRelabelComponentImageFilter.h"
#include "itkMultiplyImageFilter.h"

#include "otbMeanShiftImageFilter.h"
#include "otbMeanShiftImageFilter2.h"
#include "otbMeanShiftVectorImageFilter.h"
#include "itkMacro.h"


namespace otb
{

/**
 * \class LabeledOutputAccessor
 * \brief Accessor to the index of the labeled output image of the Template Filter.
 */
template <class TFilter>
class LabeledOutputAccessor
{
   public:
      typedef typename TFilter::OutputImageType    LabelImageType;
      itkStaticConstMacro(LabeledOutputIndex, unsigned int, 0);
};

/**
 * \class LabeledOutputAccessor
 * \brief Specialized class to get the index of the labeled output image in mean shift filter.
 */
template <class TInputImage, class TOutputImage, class TLabeledImage, class TBufferConverter>
class LabeledOutputAccessor<MeanShiftImageFilter<TInputImage, TOutputImage, TLabeledImage, TBufferConverter> >
{
   public:
      typedef typename MeanShiftImageFilter<TInputImage, TOutputImage, TLabeledImage, TBufferConverter>::LabeledOutputType    LabelImageType;
      itkStaticConstMacro(LabeledOutputIndex, unsigned int, 2);
};

/**
 * \class LabeledOutputAccessor
 * \brief Specialized class to get the index of the labeled output image in mean shift vector image filter.
 */
template <class TInputImage, class TOutputImage, class TLabeledImage>
class LabeledOutputAccessor<MeanShiftVectorImageFilter<TInputImage, TOutputImage, TLabeledImage> >
{
   public:
      typedef typename MeanShiftVectorImageFilter<TInputImage, TOutputImage, TLabeledImage>::LabeledOutputType    LabelImageType;
      itkStaticConstMacro(LabeledOutputIndex, unsigned int, 2);
};

/**
 * \class LabeledOutputAccessor
 * \brief Specialized class to get the index of the labeled output image in mean shift filter (new version).
 */
template <class TInputImage, class TOutputImage, class TOutputImage2, class TKernelType>
class LabeledOutputAccessor<MeanShiftImageFilter2<TInputImage, TOutputImage, TOutputImage2, TKernelType> >
{
   public:
      typedef typename MeanShiftImageFilter2<TInputImage, TOutputImage, TOutputImage2, TKernelType>::LabeledOutputType    LabelImageType;
      itkStaticConstMacro(LabeledOutputIndex, unsigned int, 0);
};

/** \class PersistentStreamingLabelImageToOGRDataFilter
 * \brief This filter is a framework for large scale segmentation.
 * It is a persistent filter that process the input image tile by tile.
 * The segmentation filter is set by the user using \c SetSegmentationFilter.
 * The result of the segmentation of each tile is vectorized using \c GDALPolygonize()
 * and then the result is written in a \c ogr::DataSource.
 *
 */
template <class TImageType,  class TSegmentationFilter>
class PersistentStreamingLabelImageToOGRDataFilter
  : public otb::PersistentImageToOGRDataFilter<TImageType>
{
public:
  /** Standard Self typedef */
  typedef PersistentStreamingLabelImageToOGRDataFilter     Self;
  typedef PersistentImageToOGRDataFilter<TImageType>       Superclass;
  typedef itk::SmartPointer<Self>                          Pointer;
  typedef itk::SmartPointer<const Self>                    ConstPointer;

  typedef typename Superclass::InputImageType              InputImageType;
  typedef typename Superclass::InputImagePointer           InputImagePointerType;

  typedef TSegmentationFilter                              SegmentationFilterType;
  typedef typename LabeledOutputAccessor<SegmentationFilterType>::LabelImageType  LabelImageType;
  typedef typename LabelImageType::PixelType                                      LabelPixelType;
  
  typedef otb::LabelImageToOGRDataSourceFilter<LabelImageType>          LabelImageToOGRDataSourceFilterType;
  typedef typename Superclass::OGRDataSourceType                        OGRDataSourceType;
  typedef typename Superclass::OGRDataSourcePointerType                 OGRDataSourcePointerType;
  typedef typename Superclass::OGRLayerType                             OGRLayerType;
  
  typedef RelabelComponentImageFilter<LabelImageType,LabelImageType>    RelabelComponentImageFilterType;
  typedef itk::MultiplyImageFilter<LabelImageType,LabelImageType,LabelImageType>  MultiplyImageFilterType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(PersistentStreamingLabelImageToOGRDataFilter, PersistentImageToOGRDataFilter);
  
  /** Return a pointer to the segmentation filter used. */
  itkGetObjectMacro(SegmentationFilter, SegmentationFilterType);
  
  /** Set the first Label value (default is 1). Incremental step is 1.*/
  void SetStartLabel(const LabelPixelType & label)
  {
     m_StartLabel = label;
     m_TileMaxLabel = label;
  }
  /** Return the first label value*/
  itkGetMacro(StartLabel, LabelPixelType);
  
  /**
   * Set the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  itkSetMacro(Use8Connected, bool);
  /**
   * Get the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  itkGetMacro(Use8Connected, bool);
  
  /** Set the option for filtering small objects. Default to false. */
  itkSetMacro(FilterSmallObject, bool);
  /** Return the value of filter small objects option.*/
  itkGetMacro(FilterSmallObject, bool);
  
  /** Set the minimum object size (in pixels) in case FilterSmallObject option is true.*/
  itkSetMacro(MinimumObjectSize, unsigned int);
  /** Get the minimum object size.*/
  itkGetMacro(MinimumObjectSize, unsigned int);
  
  /** Option for simplifying geometries. Default to false.*/
  itkSetMacro(Simplify, bool);
  itkGetMacro(Simplify, bool);
  
  /** Set the tolerance value for simplifying geometries.
   * \sa \c OGRGeometry::Simplify() \c OGRGeometry::SimplifyPreserveTopology()
   */
  itkSetMacro(SimplificationTolerance, double);
  /** Get the tolerance value for simplifying geometries.
   * \sa \c OGRGeometry::Simplify() \c OGRGeometry::SimplifyPreserveTopology()
   */
  itkGetMacro(SimplificationTolerance, double);
  
  /** Set/Get the input mask image.
   * All pixels in the mask with a value of 0 will not be considered
   * suitable for vectorization.
   */
  virtual void SetInputMask(const LabelImageType *mask);
  virtual const LabelImageType * GetInputMask(void);

protected:
  PersistentStreamingLabelImageToOGRDataFilter();

  virtual ~PersistentStreamingLabelImageToOGRDataFilter();

  void GenerateInputRequestedRegion();

private:
  PersistentStreamingLabelImageToOGRDataFilter(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented

  virtual OGRDataSourcePointerType ProcessTile();
  

  int m_TileMaxLabel;
  LabelPixelType m_StartLabel;
  typename SegmentationFilterType::Pointer m_SegmentationFilter;
  
  unsigned int m_TileNumber;
  bool m_Use8Connected;
  bool m_FilterSmallObject;
  unsigned int m_MinimumObjectSize;
  bool m_Simplify;
  double m_SimplificationTolerance;
  
  
};

/** \class StreamingVectorizedSegmentationOGR
 * \brief This filter is a framework for large scale segmentation.
 * It is a persistent filter that process the input image tile by tile.
 * The segmentation filter is set by the user using \c SetSegmentationFilter.
 * The result of the segmentation of each tile is vectorized using \c GDALPolygonize()
 * and then the result is written in a \c ogr::DataSource.
 *
 *
 */
template <class TImageType,  class TSegmentationFilter>
class ITK_EXPORT StreamingVectorizedSegmentationOGR :
public PersistentFilterStreamingDecorator<PersistentStreamingLabelImageToOGRDataFilter<TImageType, TSegmentationFilter> >
{

public:
  /** Standard Self typedef */
  typedef StreamingVectorizedSegmentationOGR Self;
  typedef PersistentFilterStreamingDecorator
  <PersistentStreamingLabelImageToOGRDataFilter<TImageType, TSegmentationFilter> >   Superclass;
  typedef itk::SmartPointer<Self>                                                    Pointer;
  typedef itk::SmartPointer<const Self>                                              ConstPointer;

  /** Type macro */
  itkNewMacro(Self);

  /** Creation through object factory macro */
  itkTypeMacro(StreamingVectorizedSegmentationOGR, PersistentFilterStreamingDecorator);

  typedef TSegmentationFilter                      SegmentationFilterType;
  typedef TImageType                               InputImageType;
  typedef typename PersistentStreamingLabelImageToOGRDataFilter<TImageType,
               TSegmentationFilter>::LabelPixelType                           LabelPixelType;
  typedef typename PersistentStreamingLabelImageToOGRDataFilter<TImageType,
               TSegmentationFilter>::LabelImageType                           LabelImageType;
  typedef typename PersistentStreamingLabelImageToOGRDataFilter<TImageType,
               TSegmentationFilter>::OGRDataSourcePointerType                 OGRDataSourcePointerType;

  /** Set the input image. */
  void SetInput(InputImageType * input)
  {
    this->GetFilter()->SetInput(input);
  }
  const InputImageType * GetInput()
  {
    return this->GetFilter()->GetInput();
  }
  /** Set/Get the input mask image.
   * All pixels in the mask with a value of 0 will not be considered
   * suitable for vectorization.
   */
  void SetInputMask(LabelImageType * mask)
  {
    this->GetFilter()->SetInputMask(mask);
  }
  const LabelImageType * GetInputMask()
  {
    return this->GetFilter()->GetInputMask();
  }
  /** Set the \c ogr::DataSource in which the layer LayerName will be created. */
  void SetOGRDataSource( OGRDataSourcePointerType ogrDS )
  {
    this->GetFilter()->SetOGRDataSource(ogrDS);
  }

  SegmentationFilterType * GetSegmentationFilter()
  {
     return this->GetFilter()->GetSegmentationFilter();
  }
  /** Set the Field Name in which labels will be written. (default is "DN")
   * A field FieldName is created in the output layer LayerName. The Field type is Integer.
   */
  void SetFieldName(const std::string & field)
  {
     this->GetFilter()->SetFieldName(field);
  }
  
  const std::string & GetFieldName()
  {
     return this->GetFilter()->GetFieldName();
  }
  
  /** Set the first Label value (default is 1). Incremental step is 1.*/
  void SetStartLabel(const LabelPixelType & label)
  {
     this->GetFilter()->SetStartLabel(label);
  }
  /** Return the first label value*/
  const LabelPixelType & GetStartLabel()
  {
     return this->GetFilter()->GetStartLabel();
  }
  /** Set/Get the name of the output layer to write in the input \c ogr::DataSource. */
  void SetLayerName(const std::string & fileName)
  {
     this->GetFilter()->SetLayerName(fileName);
  }
  
  void Initialize()
  {
     this->GetFilter()->Initialize();
  }
  /**
   * Set the value of 8-connected neighborhood option used in \c LabelImageToOGRDataSourceFilter
   */
  void SetUse8Connected(bool flag)
  {
     this->GetFilter()->SetUse8Connected(flag);
  }
  
  const bool GetUse8Connected()
  {
     return this->GetFilter()->GetUse8Connected();
  }
  /** Set the option for filtering small objects. Default to false. */
  void SetFilterSmallObject(bool flag)
  {
     this->GetFilter()->SetFilterSmallObject(flag);
  }
  
  const bool GetFilterSmallObject()
  {
     return this->GetFilter()->GetFilterSmallObject();
  }
  /** Set the minimum object size (in pixels) in case FilterSmallObject option is true.*/
  void SetMinimumObjectSize(const unsigned int & size)
  {
     this->GetFilter()->SetMinimumObjectSize(size);
  }
  
  const unsigned int GetMinimumObjectSize()
  {
     return this->GetFilter()->GetMinimumObjectSize();
  }
  /** Option for simplifying geometries. Default to false.*/
  void SetSimplify(bool flag)
  {
     this->GetFilter()->SetSimplify(flag);
  }
  
  const bool GetSimplify()
  {
     return this->GetFilter()->GetSimplify();
  }
  /** Set the tolerance value for simplifying geometries.
   * \sa \c OGRGeometry::Simplify() \c OGRGeometry::SimplifyPreserveTopology()
   */
  void SetSimplificationTolerance(const double & tol)
  {
     this->GetFilter()->SetSimplificationTolerance(tol);
  }
  
  const double GetSimplificationTolerance()
  {
     return this->GetFilter()->GetSimplificationTolerance();
  }
  
protected:
  /** Constructor */
  StreamingVectorizedSegmentationOGR() {}
  /** Destructor */
  virtual ~StreamingVectorizedSegmentationOGR() {}

private:
  StreamingVectorizedSegmentationOGR(const Self &); //purposely not implemented
  void operator =(const Self&); //purposely not implemented
};


}

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbStreamingVectorizedSegmentationOGR.txx"
#endif

#endif
