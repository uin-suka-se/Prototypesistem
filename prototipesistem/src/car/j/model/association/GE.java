package car.j.model.association;

import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;
import car.j.model.Engine;
import car.j.model.Gearbox;

public class GE extends Association{
	public class g extends End<One<Gearbox>> {
	}

	public class e extends End<One<Engine>> {
	}

}
