package car.x.model;

import car.x.model.LightOff;
import car.x.model.SwitchLight;
import hu.elte.txtuml.api.model.From;
import hu.elte.txtuml.api.model.ModelClass;
import hu.elte.txtuml.api.model.StateMachine;
import hu.elte.txtuml.api.model.To;
import hu.elte.txtuml.api.model.Trigger;

@SuppressWarnings("all")
public class Lamp extends ModelClass {
  public class Init extends StateMachine.Initial {
  }
  
  public class Dark extends StateMachine.State {
  }
  
  public class Light extends StateMachine.State {
  }
  
  @From(Lamp.Init.class)
  @To(Lamp.Dark.class)
  public class Init_Dark extends StateMachine.Transition {
  }
  
  @From(Lamp.Dark.class)
  @To(Lamp.Light.class)
  @Trigger(SwitchLight.class)
  public class Dark_Light extends StateMachine.Transition {
  }
  
  @From(Lamp.Light.class)
  @To(Lamp.Dark.class)
  @Trigger(SwitchLight.class)
  public class Light_Dark extends StateMachine.Transition {
  }
  
  @From(Lamp.Light.class)
  @To(Lamp.Dark.class)
  @Trigger(LightOff.class)
  public class Light_Dark2 extends StateMachine.Transition {
  }
}
