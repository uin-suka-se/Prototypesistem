#ifndef __ASSOCIATIONINSTANCES_HPP__
#define __ASSOCIATIONINSTANCES_HPP__

#include "runtime/AssociationUtils.hpp"
#include "AssoctaionEndDescriptors.hpp"
namespace Model {
extern Association<GLDescriptor::gEnd, GLDescriptor::lEnd> GL;
extern Association<LEDescriptor::lEnd, LEDescriptor::eEnd> LE;
extern Association<GEDescriptor::gEnd, GEDescriptor::eEnd> GE;

}

#endif //__ASSOCIATIONINSTANCES_HPP_

