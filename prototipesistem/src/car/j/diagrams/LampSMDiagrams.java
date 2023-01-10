package car.j.diagrams;

import hu.elte.txtuml.api.layout.Above;
import hu.elte.txtuml.api.layout.Left;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.j.model.Lamp.Dark;
import car.j.model.Lamp.Init;
import car.j.model.Lamp.Light;
import car.j.model.Lamp;

public class LampSMDiagrams extends StateMachineDiagram<Lamp>{
	
	@Above(from=Light.class, val = Init.class)
	@Left(from=Dark.class, val=Light.class)
	class L extends Layout{}

}

