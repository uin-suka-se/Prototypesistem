package car.x.model;

import car.x.model.Backward;
import car.x.model.Engine;
import car.x.model.EngineOff;
import car.x.model.EngineOn;
import car.x.model.Forward;
import car.x.model.Lamp;
import car.x.model.LightOff;
import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.From;
import hu.elte.txtuml.api.model.ModelClass;
import hu.elte.txtuml.api.model.StateMachine;
import hu.elte.txtuml.api.model.To;
import hu.elte.txtuml.api.model.Trigger;

@SuppressWarnings("all")
public class Gearbox extends ModelClass {
  public class Init extends StateMachine.Initial {
  }
  
  public class Neutral extends StateMachine.State {
  }
  
  public class Forwards extends StateMachine.CompositeState {
    public class FInit extends StateMachine.Initial {
    }
    
    public class F1 extends StateMachine.State {
    }
    
    public class F2 extends StateMachine.State {
    }
    
    @From(Gearbox.Forwards.FInit.class)
    @To(Gearbox.Forwards.F1.class)
    public class FInit_F1 extends StateMachine.Transition {
    }
    
    @From(Gearbox.Forwards.F1.class)
    @To(Gearbox.Forwards.F2.class)
    @Trigger(Forward.class)
    public class F1_F2 extends StateMachine.Transition {
    }
    
    @From(Gearbox.Forwards.F2.class)
    @To(Gearbox.Forwards.F1.class)
    @Trigger(Forward.class)
    public class F2_F1 extends StateMachine.Transition {
    }
  }
  
  public class Backwards extends StateMachine.CompositeState {
    public class BInit extends StateMachine.Initial {
    }
    
    public class B1 extends StateMachine.State {
    }
    
    public class B2 extends StateMachine.State {
    }
    
    @From(Gearbox.Backwards.BInit.class)
    @To(Gearbox.Backwards.B1.class)
    public class BInit_B1 extends StateMachine.Transition {
    }
    
    @From(Gearbox.Backwards.B1.class)
    @To(Gearbox.Backwards.B2.class)
    @Trigger(Backward.class)
    public class B1_B2 extends StateMachine.Transition {
    }
    
    @From(Gearbox.Backwards.B2.class)
    @To(Gearbox.Backwards.B1.class)
    @Trigger(Backward.class)
    public class B2_B1 extends StateMachine.Transition {
    }
  }
  
  @From(Gearbox.Init.class)
  @To(Gearbox.Neutral.class)
  public class Init_Neutral extends StateMachine.Transition {
  }
  
  @From(Gearbox.Neutral.class)
  @To(Gearbox.Forwards.class)
  @Trigger(Forward.class)
  public class Neutral_Forwards extends StateMachine.Transition {
    @Override
    public void effect() {
      Gearbox.this.startEngineOp();
    }
  }
  
  @From(Gearbox.Neutral.class)
  @To(Gearbox.Backwards.class)
  @Trigger(Backward.class)
  public class Neutral_Backwards extends StateMachine.Transition {
    @Override
    public void effect() {
      Gearbox.this.startEngineOp();
    }
  }
  
  @From(Gearbox.Forwards.class)
  @To(Gearbox.Neutral.class)
  @Trigger(Backward.class)
  public class Forwards_Neutral extends StateMachine.Transition {
    @Override
    public void effect() {
      Engine e = Gearbox.this.assoc(car.x.model.GE.e.class).one();
      Action.send(new EngineOff(), e);
      Lamp l = Gearbox.this.assoc(car.x.model.GL.l.class).one();
      Action.send(new LightOff(), l);
    }
  }
  
  @From(Gearbox.Backwards.class)
  @To(Gearbox.Neutral.class)
  @Trigger(Forward.class)
  public class Backwards_Neutral extends StateMachine.Transition {
    @Override
    public void effect() {
      Engine e = Gearbox.this.assoc(car.x.model.GE.e.class).one();
      Action.send(new EngineOff(), e);
      Lamp l = Gearbox.this.assoc(car.x.model.GL.l.class).one();
      Action.send(new LightOff(), l);
    }
  }
  
  void startEngineOp() {
    Engine e = this.assoc(car.x.model.GE.e.class).one();
    Action.send(new EngineOn(), e);
  }
}
