/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2017-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#pragma once

#include "fwRenderOgre/vr/RayTracingVolumeRenderer.hpp"

namespace fwRenderOgre
{
namespace vr
{

/**
 * @brief Importance driven volume renderer, extends the standard ray tracing renderer.
 */
class FWRENDEROGRE_CLASS_API ImportanceDrivenVolumeRenderer : public RayTracingVolumeRenderer
{
public:

    enum class IDVRCSGModulationMethod
    {
        AVERAGE_GRAYSCALE,
        LIGHTNESS_GRAYSCALE,
        LUMINOSITY_GRAYSCALE,
        COLOR1,
        COLOR2,
        COLOR3,
        COLOR4
    };

    FWRENDEROGRE_API ImportanceDrivenVolumeRenderer(std::string parentId,
                                                    Layer::sptr layer,
                                                    ::Ogre::SceneNode* parentNode,
                                                    ::Ogre::TexturePtr imageTexture,
                                                    ::Ogre::TexturePtr maskTexture,
                                                    const TransferFunction::sptr& gpuTF,
                                                    PreIntegrationTable& preintegrationTable,
                                                    bool ambientOcclusion,
                                                    bool colorBleeding,
                                                    bool shadows               = false,
                                                    double aoFactor            = 1.,
                                                    double colorBleedingFactor = 1.);

    FWRENDEROGRE_API virtual ~ImportanceDrivenVolumeRenderer();

    /// Allows to setup the importance driven method used during the rendering.
    FWRENDEROGRE_API void setIDVRMethod(std::string method);

    /// Toggle countersink geometry when using Importance Driven Volume Rendering.
    FWRENDEROGRE_API void toggleIDVRCountersinkGeometry(bool);

    /// Setup the countersink geometry slope used in the MImP method.
    FWRENDEROGRE_API void setIDVRCountersinkSlope(double);

    /// Setup the countersink geometry blur weight factor used in the MImP method.
    FWRENDEROGRE_API void setIDVRCSGBlurWeight(double);

    /// Toggle countersink geometry border used in the MImP method.
    FWRENDEROGRE_API void toggleIDVRCSGBorder(bool);

    /// Toggle context discard when using MImP countersink geometry.
    FWRENDEROGRE_API void toggleIDVRCSGDisableContext(bool);

    /// Setup the countersink geometry border thickness used in the MImP method.
    FWRENDEROGRE_API void setIDVRCSGBorderThickness(double);

    /// Setup the countersink geometry border color used in the MImP method.
    FWRENDEROGRE_API void setIDVRCSGBorderColor(std::array<std::uint8_t, 4>);

    /// Toggle the grayscale modulation for MImP countersink geometry.
    FWRENDEROGRE_API void toggleIDVRCSGModulation(bool);

    /// Setup the grayscale modulation method used for MImP countersink geometry.
    FWRENDEROGRE_API void setIDVRCSModulationMethod(IDVRCSGModulationMethod);

    /// Setup the wheighting factor for MImP CSG color modulation.
    FWRENDEROGRE_API void setIDVRCSGModulationFactor(double);

    /// Toggle the opacity decrease for MImP countersink geometry.
    FWRENDEROGRE_API void toggleIDVRCSGOpacityDecrease(bool);

    /// Setup the opacity decrease factor used in the MImP CSG.
    FWRENDEROGRE_API void setIDVRCSGOpacityDecreaseFactor(double);

    /// Toggle the depth lines for MImP countersink geometry.
    FWRENDEROGRE_API void toggleIDVRDepthLines(bool);

    /// Setup the alpha correction factor used in the VPImC method.
    FWRENDEROGRE_API void setIDVRAImCAlphaCorrection(double);

    /// Setup the alpha correction factor used in the VPImC method.
    FWRENDEROGRE_API void setIDVRVPImCAlphaCorrection(double);

    FWRENDEROGRE_API void setImageSpacing(const ::Ogre::Vector3& _spacing);

    /// Slot: Called when the size of the viewport changes.
    FWRENDEROGRE_API virtual void resizeViewport(int w, int h) override;

protected:

    /// Updates the current compositor name according to VR effects flags.
    /// @return tuple containing a
    /// - Comma separated list of preprocessor defines to use in vertex shaders.
    /// - Comma separated list of preprocessor defines to use in fragment shaders.
    /// - Hash allowing to identify the material
    FWRENDEROGRE_API virtual std::tuple<std::string, std::string, size_t> computeRayTracingDefines() const override;

    /// Sets all texture units needed by the material during the ray casting pass.
    FWRENDEROGRE_API virtual void setRayCastingPassTextureUnits(::Ogre::Pass* _rayCastingPass,
                                                                const std::string& _fpPPDefines) const override;

private:

    /// Adds the IDVR technique to the volume ray tracing material.
    void createIDVRTechnique();

    /// Generates the material with the IDVR technique.
    void createMaterialAndIDVRTechnique();

    /// Initializes the compositors used after the step computing the ray entry points
    void initCompositors();

    /// Creates and adds importance compositing compositors to the chain (MImP + JFA, AImC or VPImC).
    void buildICCompositors(::Ogre::Viewport* _vp);

    /// Removes all listeners and compositors from the current chain.
    void cleanCompositorChain(::Ogre::Viewport* _vp);

    /// Texture of the segmentation mask.
    ::Ogre::TexturePtr m_maskTexture;

    /// Name of the method used for Importance driven volume rendering
    std::string m_idvrMethod;

    /// Sets usage of countersink geometry for MImP.
    bool m_idvrCSG;

    /// Sets countersink geometry slope for MImP.
    float m_idvrCSGSlope;

    /// Sets countersink geometry blur weight for MImP.
    float m_idvrCSGBlurWeight;

    /// Sets usage of countersink geometry border for MImP.
    bool m_idvrCSGBorder;

    /// Sets whether or not the context should be discarded when using MImP countersink geometry.
    bool m_idvrCSGDisableContext;

    /// Sets countersink geometry border thickness for MImP.
    float m_idvrCSGBorderThickness;

    /// Sets countersink geometry border color for MImP.
    ::Ogre::ColourValue m_idvrCSGBorderColor;

    /// Sets usage of modulation for MImP CSG.
    bool m_idvrCSGModulation;

    /// Name of the method used to compute the new color values in CSG.
    IDVRCSGModulationMethod m_idvrCSGModulationMethod;

    /// Sets the wheighting factor for MImP CSG color modulation.
    float m_idvrCSGModulationFactor;

    /// Sets usage of opacity decrease for MImP CSG.
    bool m_idvrCSGOpacityDecrease;

    /// Sets the opacity decrease factor used in MImP CSG.
    float m_idvrCSGOpacityDecreaseFactor;

    /// Sets usage of depth lines for MImP CSG.
    bool m_idvrCSGDepthLines;

    /// Sets the alpha correction for AImC.
    float m_idvrAImCAlphaCorrection;

    /// Sets the alpha correction for VPImC.
    float m_idvrVPImCAlphaCorrection;

    /// Compositor listener classes used to upload uniforms for mono/stereo ray tracing materials.
    class JFACompositorListener;

    /// List of all listeners associated to the VR's compositor chain.
    /// If a compositor has no listener, we store a nullptr in the corresponding entry.
    std::vector< ::Ogre::CompositorInstance::Listener*> m_compositorListeners;

};

} // namespace vr
} // namespace fwRenderOgre
