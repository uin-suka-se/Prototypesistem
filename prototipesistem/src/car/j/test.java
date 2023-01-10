package car.j;

import hu.elte.txtuml.api.model.API;
import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.execution.Execution;
import hu.elte.txtuml.api.model.execution.LogLevel;
import car.j.test;
import car.j.model.Engine;
import car.j.model.Gearbox;
import car.j.model.Lamp;
import car.j.model.association.GE;
import car.j.model.association.GL;
import car.j.model.association.LE;
import car.j.model.signals.Backward;
import car.j.model.signals.Forward;
import car.j.model.signals.SwitchLight;


public class test implements Execution {
	
	@Override
	public void configure(Settings s) {
		s.logLevel = LogLevel.TRACE;
	}

	Gearbox g;
	Engine e;
	Lamp l;

	@Override
	public void initialization() {
		g = Action.create(Gearbox.class);
		e = Action.create(Engine.class);
		l = Action.create(Lamp.class);
		Action.link(GE.g.class, g, GE.e.class, e);
		Action.link(GL.g.class, g, GL.l.class, l);
		Action.link(LE.l.class, l, LE.e.class, e);
		Action.start(g);
		Action.start(e);
		Action.start(l);
	}

	@Override
	public void during() {
		try {
			int time = 50;
			for (int i = 0; i < 3; i++) {
				Thread.sleep(time);
				API.log("");
				API.send(new SwitchLight(), l);
			}

			Thread.sleep(2 * time);

			for (int i = 0; i < 3; i++) {
				Thread.sleep(3 * time);
				API.log("");
				API.send(new Forward(), g);

				Thread.sleep(time);
				API.log("");
				API.send(new Backward(), g);
			}

		} catch (InterruptedException e) {
		}
	}

	public static void main(String[] args) throws Exception {
		new test().run();
	}
}
