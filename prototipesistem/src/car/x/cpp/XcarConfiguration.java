package car.x.cpp;

import hu.elte.txtuml.api.deployment.Configuration;
import hu.elte.txtuml.api.deployment.Group;
import hu.elte.txtuml.api.deployment.Runtime;
import hu.elte.txtuml.api.deployment.RuntimeType;
import car.x.model.Engine;
import car.x.model.Gearbox;

@Group(contains = { Engine.class, Gearbox.class }, max = 5, constant = 2)
@Runtime(RuntimeType.THREADED)
public class XcarConfiguration extends Configuration {

}
