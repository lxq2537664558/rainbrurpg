/*
 *  Copyright 2006-2012 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef _DUMMY_RENDER_SYSTEM_HPP_
#define _DUMMY_RENDER_SYSTEM_HPP_

#include <OgrePrerequisites.h>
#include <OgreRenderSystem.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#  ifdef DUMMY_RS_EXPORT
#    define _Dummy_RS_Export_ __declspec(dllexport) 
#  else
#    define _Dummy_RS_Export_ __declspec(dllimport) 
#  endif
#else
#  define _Dummy_RS_Export_
#endif

using namespace Ogre;

/** An Ogre renderer that does nothing
  *
  * To avoid the need of Xorg when running unit tests.
  *
  */
class DummyRenderSystem : public Ogre::RenderSystem
{
public:
  DummyRenderSystem();
  virtual ~DummyRenderSystem();

  // OgrePlugin interface
  void install(void);
  void uninstall(void);
  void initialise(void){};
  void shutdown(void){};

  // RenderSystem interface
  HardwareOcclusionQuery* createHardwareOcclusionQuery(void);
  RenderWindow* createRenderWindow(const String&, unsigned int, 
				   unsigned int, bool, 
				   const NameValuePairList*);
  MultiRenderTarget* createMultiRenderTarget(const String&); 


  const String& getName(void) const;
  ConfigOptionMap& getConfigOptions(void);
  void setConfigOption(const String&, const String&){ };
  String validateConfigOptions(void){ return ""; };
  void reinitialise(void){};
  void setAmbientLight(float, float, float){};
  void setShadingType(ShadeOptions){};
  void setLightingEnabled(bool){};


  void registerThread(void){ };
  void unregisterThread(void){ };
  void preExtraThreadsStarted(){ };
  void postExtraThreadsStarted(){ };

  Real getMinimumDepthInputValue(){ return 1.0f; };
  Real getMaximumDepthInputValue(){ return 1.0f; };
  Real getHorizontalTexelOffset() { return 1.0f; };
  Real getVerticalTexelOffset() { return 1.0f; };

  void clearFrameBuffer(unsigned int, const ColourValue&, Real, short unsigned int){};
  void setScissorTest(bool, size_t,  size_t,  size_t,  size_t){ };
  void enableClipPlane(Ogre::ushort, bool){};
  void setClipPlane(Ogre::ushort, Real, Real, Real, Real){};
  void setClipPlanes(const Ogre::PlaneList&){};

  Ogre::String getErrorDescription(long int) const{ return ""; };
  void _useLights(const LightList&, short unsigned int){};
  void _setWorldMatrix(const Matrix4&){};
  void _setViewMatrix(const Matrix4&){};
  void _setProjectionMatrix(const Matrix4&){};

  void _setSurfaceParams(const ColourValue&, const ColourValue&, 
			 const ColourValue&, const ColourValue&, 
			 Real, TrackVertexColourType){};
  void _setPointSpritesEnabled(bool){};
  void _setPointParameters(Real, bool, Real, Real, Real, Real, Real){};
  void _setTexture(size_t, bool, const TexturePtr&){};
  void _setTextureCoordSet(size_t, size_t){};

  void _setTextureCoordCalculation(size_t, TexCoordCalcMethod, const Frustum*){};
  void _setTextureBlendMode(size_t, const LayerBlendModeEx&){};
  void _setTextureUnitFiltering(size_t, FilterType, FilterOptions){};
  void _setTextureLayerAnisotropy(size_t, unsigned int){};
  void _setTextureAddressingMode(size_t, const TextureUnitState::UVWAddressingMode&){};
  void _setTextureBorderColour(size_t, const ColourValue&){};
  void _setTextureMipmapBias(size_t, float){};
  void _setTextureMatrix(size_t, const Matrix4&){};
  void _setSceneBlending(SceneBlendFactor, SceneBlendFactor){};
  void _setAlphaRejectSettings(CompareFunction, unsigned char){};
  void _beginFrame(){};
  void _endFrame(){};

  void _setViewport(Viewport*){};
  void _setCullingMode(CullingMode){};
  void _setDepthBufferParams(bool, bool, CompareFunction){};
  void _setDepthBufferCheckEnabled(bool){};
  void _setDepthBufferWriteEnabled(bool){};
  void _setDepthBufferFunction(CompareFunction){};
  void _setColourBufferWriteEnabled(bool, bool, bool, bool){};
  void _setDepthBias(float, float){};
  void _setFog(FogMode, const ColourValue&, Real, Real, Real){};

  void _convertProjectionMatrix(const Matrix4&, Matrix4&, bool){};
  void _makeProjectionMatrix(const Radian&, Real, Real, Real, Matrix4&, bool){};
  void _makeProjectionMatrix(Real, Real, Real, Real, Real, Real, Matrix4&, bool){};

  void _makeOrthoMatrix(const Radian&, Real, Real, Real, Matrix4&, bool){};
  void _applyObliqueDepthProjection(Matrix4&, const Plane&, bool){};
  void _setPolygonMode(PolygonMode){};
  void setStencilCheckEnabled(bool){};
  void setStencilBufferParams(CompareFunction, uint32, uint32, 
			      StencilOperation, StencilOperation, 
			      StencilOperation, bool){};

  void setVertexDeclaration(VertexDeclaration*){};
  void setVertexBufferBinding(VertexBufferBinding*){};
  void setNormaliseNormals(bool){};
  void bindGpuProgramParameters(GpuProgramType, GpuProgramParametersSharedPtr){};
  void bindGpuProgramPassIterationParameters(GpuProgramType){};
  VertexElementType getColourVertexElementType() const{ return VET_UBYTE4; };




  virtual RenderSystemCapabilities* createRenderSystemCapabilities() const;
  virtual RenderWindow* _createRenderWindow(const String&, unsigned int, unsigned int, bool, const NameValuePairList*);
  virtual void _setSeparateSceneBlending(SceneBlendFactor, SceneBlendFactor, SceneBlendFactor, SceneBlendFactor);
  virtual void _setAlphaRejectSettings(CompareFunction, unsigned char, bool);
  virtual void setClipPlanesImpl(const PlaneList&);
  virtual void initialiseFromRenderSystemCapabilities(RenderSystemCapabilities*, RenderTarget*);


  virtual void _setSceneBlending(Ogre::SceneBlendFactor, Ogre::SceneBlendFactor, Ogre::SceneBlendOperation){};

  virtual void _setSeparateSceneBlending(Ogre::SceneBlendFactor, Ogre::SceneBlendFactor, Ogre::SceneBlendFactor, Ogre::SceneBlendFactor, Ogre::SceneBlendOperation, Ogre::SceneBlendOperation){};

  virtual void bindGpuProgramParameters(Ogre::GpuProgramType, Ogre::GpuProgramParametersSharedPtr, Ogre::uint16){};

  virtual void _setRenderTarget(Ogre::RenderTarget*){};
  virtual unsigned int getDisplayMonitorCount() const{};

  virtual DepthBuffer* _createDepthBufferFor(RenderTarget*){};

  virtual void beginProfileEvent(const String&){};
  virtual void endProfileEvent(){};
  virtual void markProfileEvent(const String&){};

private:
  String mName;
  ConfigOptionMap mConfigOptionMap;
};

#endif // !_DUMMY_RENDER_SYSTEM_HPP_
