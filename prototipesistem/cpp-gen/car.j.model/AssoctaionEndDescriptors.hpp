#ifndef __ASSOCTAIONENDDESCRIPTORS_HPP__
#define __ASSOCTAIONENDDESCRIPTORS_HPP__

#include "runtime/AssociationUtils.hpp"
namespace Model {
class Gearbox;
class Lamp;
class Engine;

}
namespace Model {
struct GLDescriptor {
	struct gEnd;
	struct lEnd;
	struct gEnd: public AssocEnd<gEnd, lEnd, Gearbox, 1, 1> {
		gEnd* g = this;
	};
	struct lEnd: public AssocEnd<gEnd, lEnd, Lamp, 1, 1> {
		lEnd* l = this;
	};
};
struct LEDescriptor {
	struct lEnd;
	struct eEnd;
	struct lEnd: public AssocEnd<lEnd, eEnd, Lamp, 1, 1> {
		lEnd* l = this;
	};
	struct eEnd: public AssocEnd<lEnd, eEnd, Engine, 1, 1> {
		eEnd* e = this;
	};
};
struct GEDescriptor {
	struct gEnd;
	struct eEnd;
	struct gEnd: public AssocEnd<gEnd, eEnd, Gearbox, 1, 1> {
		gEnd* g = this;
	};
	struct eEnd: public AssocEnd<gEnd, eEnd, Engine, 1, 1> {
		eEnd* e = this;
	};
};
}

#endif //__ASSOCTAIONENDDESCRIPTORS_HPP_

