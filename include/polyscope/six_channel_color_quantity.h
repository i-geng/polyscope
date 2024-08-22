#pragma once

#include "polyscope/persistent_value.h"
#include "polyscope/polyscope.h"
#include "polyscope/render/engine.h"
#include "polyscope/render/managed_buffer.h"
#include "polyscope/standardize_data_array.h"

namespace polyscope {

template <typename QuantityT>
class SixChannelColorQuantity {
public:
  SixChannelColorQuantity(QuantityT& parent_, 
                          const std::vector<glm::vec3>& colorsEven_,
                          const std::vector<glm::vec3>& colorsOdd_);

  std::vector<std::string> addSixChannelColorRules(std::vector<std::string> rules);

  // === Members
  QuantityT& quantity;
  render::ManagedBuffer<glm::vec3> colorsEven;
  render::ManagedBuffer<glm::vec3> colorsOdd;

protected:
  std::vector<glm::vec3> colorsEvenData;
  std::vector<glm::vec3> colorsOddData;

}; // class SixChannelColorQuantity

} // namespace polyscope

#include "polyscope/six_channel_color_quantity.ipp"
