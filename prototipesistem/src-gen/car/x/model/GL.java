package car.x.model;

import car.x.model.Gearbox;
import car.x.model.Lamp;
import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;

@SuppressWarnings("all")
public class GL extends Association {
  public class g extends Association.End<One<Gearbox>> {
  }
  
  public class l extends Association.End<One<Lamp>> {
  }
}
