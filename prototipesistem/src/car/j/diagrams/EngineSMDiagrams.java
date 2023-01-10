package car.j.diagrams;

import hu.elte.txtuml.api.layout.Above;
import hu.elte.txtuml.api.layout.Left;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.j.model.Engine;
import car.j.model.Engine.Init;
import car.j.model.Engine.Stopped;
import car.j.model.Engine.Working;


public class EngineSMDiagrams extends StateMachineDiagram<Engine> {
	
	@Above(from=Stopped.class, val = Init.class)
	@Left(from=Working.class, val = Stopped.class)
	class L extends Layout{}

}