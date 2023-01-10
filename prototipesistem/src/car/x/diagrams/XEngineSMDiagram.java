package car.x.diagrams;

import hu.elte.txtuml.api.layout.Above;
import hu.elte.txtuml.api.layout.Left;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.x.model.Engine;
import car.x.model.Engine.Init;
import car.x.model.Engine.Stopped;
import car.x.model.Engine.Working;

public class XEngineSMDiagram extends StateMachineDiagram<Engine>{
	
	@Above(from=Stopped.class, val = Init.class)
	@Left(from=Working.class, val=Stopped.class)
	class L extends Layout{}

}
