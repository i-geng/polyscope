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

  if ((programEven == nullptr) || (programOdd == nullptr)) {
    createProgram();
  }

  std::shared_ptr<render::ShaderProgram> program;
  // TODO: choose even or odd program based on passed in boolean flag
  // don't read global state, because its possible it might have changed
  // in between sub-frame drawing calls
  if (state::isEvenFrame) {
    program = programEven;
  } else {
    program = programOdd;
  }

  // Set uniforms
  parent.setStructureUniforms(*program);
  parent.setSurfaceMeshUniforms(*program);
  render::engine->setMaterialUniforms(*program, "flat");
  render::engine->setCameraUniforms(*program);
  render::engine->setLightUniforms(*program);
  
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
  render::engine->setMaterial(*programEven, "flat");

  parent.setMeshGeometryAttributes(*programOdd);
  programOdd->setAttribute("a_color", colorsOdd.getIndexedRenderAttributeBuffer(parent.triangleVertexInds));
  render::engine->setMaterial(*programOdd, "flat");
}


// ========================================================
// ==========            Face Color              ==========
// ========================================================

SurfaceFaceSixChannelColorQuantity::SurfaceFaceSixChannelColorQuantity(
                                      std::string name,
                                      SurfaceMesh& mesh_,
                                      std::vector<glm::vec3> colorsEven_,
                                      std::vector<glm::vec3> colorsOdd_)
  : SurfaceSixChannelColorQuantity(name, mesh_, "face", colorsEven_, colorsOdd_) {}

void SurfaceFaceSixChannelColorQuantity::createProgram() {

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
  programEven->setAttribute("a_color", colorsEven.getIndexedRenderAttributeBuffer(parent.triangleFaceInds));
  render::engine->setMaterial(*programEven, parent.getMaterial());

  parent.setMeshGeometryAttributes(*programOdd);
  programOdd->setAttribute("a_color", colorsOdd.getIndexedRenderAttributeBuffer(parent.triangleFaceInds));
  render::engine->setMaterial(*programOdd, parent.getMaterial());
}

} // namespace polyscope
