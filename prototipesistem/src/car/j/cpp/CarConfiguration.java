package car.j.cpp;

import hu.elte.txtuml.api.deployment.Configuration;
import hu.elte.txtuml.api.deployment.Group;
import hu.elte.txtuml.api.deployment.Runtime;
import hu.elte.txtuml.api.deployment.RuntimeType;
import car.j.model.Engine;
import car.j.model.Gearbox;

@Group(contains = { Engine.class, Gearbox.class }, max = 5, constant = 2)
@Runtime(RuntimeType.THREADED)
public class CarConfiguration extends Configuration {

}
