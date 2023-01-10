package car.x.model;

import car.x.model.Engine;
import car.x.model.Lamp;
import hu.elte.txtuml.api.model.Association;
import hu.elte.txtuml.api.model.One;

@SuppressWarnings("all")
public class LE extends Association {
  public class l extends Association.End<One<Lamp>> {
  }
  
  public class e extends Association.End<One<Engine>> {
  }
}
