package car.j.diagrams;

import hu.elte.txtuml.api.layout.ClassDiagram;
import hu.elte.txtuml.api.layout.Diamond;
import car.j.model.Engine;
import car.j.model.Gearbox;
import car.j.model.Lamp;

public class CarClassDiagrams extends ClassDiagram{
	
	class TopPhantom extends Phantom {
	}

	@Diamond(bottom = Lamp.class, left = Engine.class, right = Gearbox.class, top = TopPhantom.class)
	class TrainLayout extends Layout {
	}
	
	
}
