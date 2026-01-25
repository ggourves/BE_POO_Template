#include "caracteristics.h"


caracteristics::caracteristics(String name, String value, int quantity): name(name), value(value), quantity(quantity) {}

String caracteristics::getName() { return name; }
String caracteristics::getValue() { return value; }
unsigned int caracteristics::getQuantity() { return quantity; }
void caracteristics::setQuantity(unsigned int q) { quantity = q; }