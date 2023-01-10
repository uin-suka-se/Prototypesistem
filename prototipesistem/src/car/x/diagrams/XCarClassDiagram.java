package car.x.diagrams;

import hu.elte.txtuml.api.layout.ClassDiagram;
import hu.elte.txtuml.api.layout.Diamond;
import car.x.model.Engine;
import car.x.model.Gearbox;
import car.x.model.Lamp;

public class XCarClassDiagram extends ClassDiagram {
	class TopPhantom extends Phantom {
	}

	@Diamond(bottom = Lamp.class, left = Engine.class, right = Gearbox.class, top = TopPhantom.class)
	class TrainLayout extends Layout {
	}
}