package car.j.model;

import hu.elte.txtuml.api.model.From;
import hu.elte.txtuml.api.model.ModelClass;
import hu.elte.txtuml.api.model.To;
import hu.elte.txtuml.api.model.Trigger;
import car.j.model.signals.EngineOff;
import car.j.model.signals.EngineOn;


public class Engine extends ModelClass {
	public class Init extends Initial {
	}
	
	public class Stopped extends State {
	}
	
	public class Working extends State {
	}
	
	@From(Init.class)
	@To(Stopped.class)
	class Init_Stopped extends Transition {
	}
	
	@From(Stopped.class)
	@To(Working.class)
	@Trigger(EngineOn.class)
	class Stopped_Working extends Transition {
	}

	@From(Working.class)
	@To(Stopped.class)
	@Trigger(EngineOff.class)
	class Working_Stopped extends Transition {
	}

}
