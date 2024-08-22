namespace polyscope {

template <typename QuantityT>
SixChannelColorQuantity<QuantityT>::SixChannelColorQuantity(QuantityT& quantity_,
                                                            const std::vector<glm::vec3>& colorsEven_,
                                                            const std::vector<glm::vec3>& colorsOdd_)
  : quantity(quantity_),
    colorsEven(&quantity, quantity.uniquePrefix() + "colorsEven", colorsEvenData),
    colorsOdd(&quantity, quantity.uniquePrefix() + "colorsOdd", colorsOddData),
    colorsEvenData(colorsEven_),
    colorsOddData(colorsOdd_)
  {}

template <typename QuantityT>
std::vector<std::string> SixChannelColorQuantity<QuantityT>::addSixChannelColorRules(std::vector<std::string> rules) {
  return rules;
}

} // namespace polyscope
