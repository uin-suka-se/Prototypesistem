package car.x.model;

import car.x.model.EngineOff;
import car.x.model.EngineOn;
import hu.elte.txtuml.api.model.From;
import hu.elte.txtuml.api.model.ModelClass;
import hu.elte.txtuml.api.model.StateMachine;
import hu.elte.txtuml.api.model.To;
import hu.elte.txtuml.api.model.Trigger;

@SuppressWarnings("all")
public class Engine extends ModelClass {
  public class Init extends StateMachine.Initial {
  }
  
  public class Stopped extends StateMachine.State {
  }
  
  public class Working extends StateMachine.State {
  }
  
  @From(Engine.Init.class)
  @To(Engine.Stopped.class)
  public class Init_Stopped extends StateMachine.Transition {
  }
  
  @From(Engine.Stopped.class)
  @To(Engine.Working.class)
  @Trigger(EngineOn.class)
  public class Stopped_Working extends StateMachine.Transition {
  }
  
  @From(Engine.Working.class)
  @To(Engine.Stopped.class)
  @Trigger(EngineOff.class)
  public class Working_Stopped extends StateMachine.Transition {
  }
}
