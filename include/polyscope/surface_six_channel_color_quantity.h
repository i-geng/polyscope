#pragma once

#include "polyscope/six_channel_color_quantity.h"
#include "polyscope/render/engine.h"
#include "polyscope/surface_mesh.h"

namespace polyscope {

// Forward declarations
class SurfaceMesh;
class SurfaceMeshQuantity;
class SurfaceParametrizationQuantity;

class SurfaceSixChannelColorQuantity : public SurfaceMeshQuantity, public SixChannelColorQuantity<SurfaceSixChannelColorQuantity> {
public:
  SurfaceSixChannelColorQuantity(std::string name, SurfaceMesh& mesh_, std::string definedOn_,
                                 const std::vector<glm::vec3>& colorsEven_,
                                 const std::vector<glm::vec3>& colorsOdd_);

  virtual void draw() override;
  virtual std::string niceName() override;
  virtual void refresh() override;

protected:
  const std::string definedOn;
  std::shared_ptr<render::ShaderProgram> programEven;
  std::shared_ptr<render::ShaderProgram> programOdd;

  virtual void createProgram() = 0;

}; // class SurfaceSixChannelColorQuantity

// ========================================================
// ==========           Vertex Color             ==========
// ========================================================

class SurfaceVertexSixChannelColorQuantity : public SurfaceSixChannelColorQuantity {
public:
  SurfaceVertexSixChannelColorQuantity(std::string name, SurfaceMesh& mesh_,
                                       std::vector<glm::vec3> colorsEven_,
                                       std::vector<glm::vec3> colorsOdd_);

  virtual void createProgram() override;
}; // class SurfaceVertexSixChannelColorQuantity


// ========================================================
// ==========             Face Color             ==========
// ========================================================

class SurfaceFaceSixChannelColorQuantity : public SurfaceSixChannelColorQuantity {
public:
  SurfaceFaceSixChannelColorQuantity(std::string name, SurfaceMesh& mesh_,
                                     std::vector<glm::vec3> colorsEven_,
                                     std::vector<glm::vec3> colorsOdd);

  virtual void createProgram() override;
}; // class SurfaceFaceSixChannelColorQuantity

} // namespace polyscope
