package car.j.model.association;

import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;
import car.j.model.Engine;
import car.j.model.Lamp;

public class LE extends Association {
	public class l extends End<One<Lamp>> {
	}

	public class e extends End<One<Engine>> {
	}
}
