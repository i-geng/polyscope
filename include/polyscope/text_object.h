
#pragma once

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/render/engine.h"

#include "glm/glm.hpp"

#include <memory>
#include <string>

namespace polyscope {

class TextObject : public QuantityStructure<TextObject> {
public:
  TextObject(std::string name);
  TextObject(std::string name, std::string textContent, glm::vec3 pos, float scale);

  virtual void draw() override;
  virtual std::string typeName() override;
  virtual void updateObjectSpaceBounds() override;

  virtual void drawDelayed() override;
  virtual void drawPick() override;
  virtual void buildCustomUI() override;
  virtual void buildPickUI(size_t localPickID) override;
  void setTextObjectAttributes(render::ShaderProgram &p);

protected:
  static const std::string structureTypeName;
  void buildMesh();

  std::string textContent;
  glm::vec3 position;
  float scale;

  std::unique_ptr<SurfaceMesh> textMesh;

  std::vector<glm::vec2> tCoords;
  render::ManagedBuffer<glm::vec2> textureCoords;
  std::shared_ptr<render::ShaderProgram> textRenderProgram;


}; // class TextObject

TextObject* registerTextObject(std::string name, std::string textContent,
                               glm::vec3 pos, float scale);

} // namespace polyscope

