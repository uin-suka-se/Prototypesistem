package car.x.diagrams;

import hu.elte.txtuml.api.layout.Above;
import hu.elte.txtuml.api.layout.Left;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.x.model.Lamp;
import car.x.model.Lamp.Dark;
import car.x.model.Lamp.Init;
import car.x.model.Lamp.Light;

public class XLampSMDiagram extends StateMachineDiagram<Lamp>{
	
	@Above(from=Light.class, val = Init.class)
	@Left(from=Dark.class, val=Light.class)
	class L extends Layout{}
}
