package car.x.model;

import car.x.model.Engine;
import car.x.model.Gearbox;
import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;

@SuppressWarnings("all")
public class GE extends Association {
  public class g extends Association.End<One<Gearbox>> {
  }
  
  public class e extends Association.End<One<Engine>> {
  }
}
