package car.j.tests;

import static hu.elte.txtuml.api.model.seqdiag.Sequence.assertState;
import static hu.elte.txtuml.api.model.seqdiag.Sequence.fromActor;
import static hu.elte.txtuml.api.model.seqdiag.Sequence.send;

import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.seqdiag.ExecMode;
import hu.elte.txtuml.api.model.seqdiag.ExecutionMode;
import hu.elte.txtuml.api.model.seqdiag.Position;
import hu.elte.txtuml.api.model.seqdiag.SequenceDiagram;
import car.j.model.Engine;
import car.j.model.Gearbox;
import car.j.model.Lamp;
import car.j.model.association.GE;
import car.j.model.association.GL;
import car.j.model.association.LE;
import car.j.model.signals.Backward;
import car.j.model.signals.EngineOff;
import car.j.model.signals.EngineOn;
import car.j.model.signals.Forward;
import car.j.model.signals.LightOff;
import car.j.model.signals.SwitchLight;

public class CarSequenceDiagram extends SequenceDiagram{
	
	@Position(1)
	Lamp lamp;

	@Position(2)
	Gearbox gearbox;

	@Position(3)
	Engine engine;

	@Override
	public void initialize() {
		gearbox = Action.create(Gearbox.class);
		engine = Action.create(Engine.class);
		lamp = Action.create(Lamp.class);

		Action.link(GE.g.class, gearbox, GE.e.class, engine);
		Action.link(GL.g.class, gearbox, GL.l.class, lamp);
		Action.link(LE.l.class, lamp, LE.e.class, engine);

		Action.start(gearbox);
		Action.start(engine);
		Action.start(lamp);
	}

	@Override
	@ExecutionMode(ExecMode.STRICT)
	public void run() {
		fromActor(new SwitchLight(), lamp);
		assertState(lamp, Lamp.Light.class);
		fromActor(new SwitchLight(), lamp);
		assertState(lamp, Lamp.Dark.class);
		fromActor(new SwitchLight(), lamp);

		fromActor(new Forward(), gearbox);
		assertState(gearbox, Gearbox.Forwards.F1.class);
		send(gearbox, new EngineOn(), engine);
		assertState(engine, Engine.Working.class);

		fromActor(new Forward(), gearbox);
		assertState(gearbox, Gearbox.Forwards.F2.class);
		fromActor(new Forward(), gearbox);
		assertState(gearbox, Gearbox.Forwards.F1.class);

		fromActor(new Backward(), gearbox);
		assertState(gearbox, Gearbox.Neutral.class);
		send(gearbox, new EngineOff(), engine);
		assertState(engine, Engine.Stopped.class);
		send(gearbox, new LightOff(), lamp);
		assertState(lamp, Lamp.Dark.class);

		fromActor(new Backward(), gearbox);
		assertState(gearbox, Gearbox.Backwards.B1.class);
		send(gearbox, new EngineOn(), engine);
		assertState(engine, Engine.Working.class);

		fromActor(new Backward(), gearbox);
		assertState(gearbox, Gearbox.Backwards.B2.class);
		fromActor(new Backward(), gearbox);
		assertState(gearbox, Gearbox.Backwards.B1.class);
	}

}
