package car.j.model.association;

import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;
import car.j.model.Gearbox;
import car.j.model.Lamp;

public class GL extends Association {
	public class g extends End<One<Gearbox>> {
	}

	public class l extends End<One<Lamp>> {
	}

}
