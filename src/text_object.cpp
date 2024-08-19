#include "polyscope/text_object.h"
#include <stdlib.h>

namespace polyscope {

const std::string TextObject::structureTypeName = "Text Object";

TextObject::TextObject(std::string name)
  : QuantityStructure<TextObject>(name, typeName()), 
    textureCoords(this, uniquePrefix() + "textureCoords", tCoords) { }

TextObject::TextObject(std::string name, std::string textContent_,
                       glm::vec3 pos, float scale_)
  : TextObject(name) {
  
  textContent = textContent_;
  position = pos;
  scale = scale_;
  
  textRenderProgram = render::engine->requestTextRenderer("TEXT_OBJECT", {});

  buildMesh();
  updateObjectSpaceBounds();
}

void TextObject::buildMesh() {
  float x = position.x, y = position.y, z = position.z;

  std::vector<glm::vec3> vertexPositions;
  std::vector<std::vector<size_t>> faceIndices;

//  vertexPositions.push_back(glm::vec3(x, y, z));
//  vertexPositions.push_back(glm::vec3(x, y + scale, z));
//
//  for (size_t i = 0; i < textContent.size(); i++) {
//    float x_coord = x + scale * (i + 1);
//    vertexPositions.push_back(glm::vec3(x_coord, y, z));
//    vertexPositions.push_back(glm::vec3(x_coord, y + scale, z));
//
//    size_t j = 2 * i;
//    std::vector<size_t> f1 {j, j+3, j+1};
//    std::vector<size_t> f2 {j, j+2, j+3};
//    faceIndices.push_back(f1);
//    faceIndices.push_back(f2);
//  }
  vertexPositions.push_back(glm::vec3(x, y + scale, z));
  vertexPositions.push_back(glm::vec3(x, y, z));
  vertexPositions.push_back(glm::vec3(x + scale, y, z));
  vertexPositions.push_back(glm::vec3(x + scale, y + scale, z));
  
  std::vector<size_t> f1 {0, 1, 2};
  std::vector<size_t> f2 {0, 2, 3};
  faceIndices.push_back(f1);
  faceIndices.push_back(f2);

  tCoords.push_back(glm::vec2(0.0, 0.0));
  tCoords.push_back(glm::vec2(0.0, 1.0));
  tCoords.push_back(glm::vec2(1.0, 1.0));
  tCoords.push_back(glm::vec2(1.0, 0.0));

  SurfaceMesh* s = new SurfaceMesh(name, vertexPositions, faceIndices);
  textMesh = std::unique_ptr<SurfaceMesh>(s);


  setTextObjectAttributes(*textRenderProgram);
}

void TextObject::draw() {
  if (!isEnabled()) return;


  // textMesh->draw();
  setStructureUniforms(*textRenderProgram);
  // textMesh->setMeshGeometryAttributes(*textRenderProgram); 
  textRenderProgram->draw();
}

std::string TextObject::typeName() { return structureTypeName; }

void TextObject::setTextObjectAttributes(render::ShaderProgram& p) {
  if (p.hasAttribute("a_vertexPositions")) {
    p.setAttribute("a_vertexPositions", textMesh->vertexPositions.getIndexedRenderAttributeBuffer(textMesh->triangleVertexInds));
  }
  
  if (p.hasAttribute("a_textureCoords")) {
    p.setAttribute("a_textureCoords", textureCoords.getIndexedRenderAttributeBuffer(textMesh->triangleVertexInds));
  }
}

void TextObject::updateObjectSpaceBounds() {
  objectSpaceBoundingBox = textMesh->boundingBox();
  objectSpaceLengthScale = textMesh->lengthScale();
};

void TextObject::drawDelayed() {};
void TextObject::drawPick() {};
void TextObject::buildCustomUI() {};
void TextObject::buildPickUI(size_t localPickID) {};

TextObject* registerTextObject(std::string name, std::string textContent,
                               glm::vec3 pos, float scale) {
  checkInitialized();
  TextObject* t = new TextObject(name, textContent, pos, scale);

  bool success = registerStructure(t);
  if (!success) {
    safeDelete(t);
  }
  return t;
}


} // namespace polyscope
