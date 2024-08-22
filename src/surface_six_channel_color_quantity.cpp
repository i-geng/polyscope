#include "polyscope/surface_six_channel_color_quantity.h"

#include "polyscope/polyscope.h"

namespace polyscope {

SurfaceSixChannelColorQuantity::SurfaceSixChannelColorQuantity(std::string name, 
                                                               SurfaceMesh& mesh_, 
                                                               std::string definedOn_,
                                                               const std::vector<glm::vec3>& colorsEven_,
                                                               const std::vector<glm::vec3>& colorsOdd_)
  : SurfaceMeshQuantity(name, mesh_, true),
    SixChannelColorQuantity(*this, colorsEven_, colorsOdd_),
    definedOn(definedOn_)
  {}

void SurfaceSixChannelColorQuantity::draw() {
  if (!isEnabled()) return;

  std::shared_ptr<render::ShaderProgram> program;
  if (true) {
    program = programEven;
  }

  if (program == nullptr) {
    createProgram();
  }

  // Set uniforms
  parent.setStructureUniforms(*program);
  parent.setSurfaceMeshUniforms(*program);

  program->draw();
}

std::string SurfaceSixChannelColorQuantity::niceName() {
  return name + " (" + definedOn + " six channel color)";
}

void SurfaceSixChannelColorQuantity::refresh() {
  return;
}

// ========================================================
// ==========           Vertex Color             ==========
// ========================================================

SurfaceVertexSixChannelColorQuantity::SurfaceVertexSixChannelColorQuantity(
                                        std::string name, 
                                        SurfaceMesh& mesh_,
                                        std::vector<glm::vec3> colorsEven_,
                                        std::vector<glm::vec3> colorsOdd_)
  : SurfaceSixChannelColorQuantity(name, mesh_, "vertex", colorsEven_, colorsOdd_) {}

void SurfaceVertexSixChannelColorQuantity::createProgram() {

  // clang-format off
  programEven = render::engine->requestShader("MESH",
    render::engine->addMaterialRules("flat",
      addSixChannelColorRules(
        parent.addSurfaceMeshRules(
          {"MESH_PROPAGATE_COLOR", "SHADE_COLOR"}
        )
      )
    )
  );
  
  programOdd = render::engine->requestShader("MESH",
    render::engine->addMaterialRules("flat",
      addSixChannelColorRules(
        parent.addSurfaceMeshRules(
          {"MESH_PROPAGATE_COLOR", "SHADE_COLOR"}
        )
      )
    )
  );
  // clang-format on

  // Set attributes
  parent.setMeshGeometryAttributes(*programEven);
  programEven->setAttribute("a_color", colorsEven.getIndexedRenderAttributeBuffer(parent.triangleVertexInds));
  render::engine->setMaterial(*programEven, parent.getMaterial());

  parent.setMeshGeometryAttributes(*programOdd);
  programOdd->setAttribute("a_color", colorsOdd.getIndexedRenderAttributeBuffer(parent.triangleVertexInds));
  render::engine->setMaterial(*programOdd, parent.getMaterial());
}

} // namespace polyscope
