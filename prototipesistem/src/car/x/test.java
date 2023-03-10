package car.x;

import hu.elte.txtuml.api.model.API;
import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.execution.Execution;
import hu.elte.txtuml.api.model.execution.LogLevel;
import car.x.test;
import car.x.model.Backward;
import car.x.model.Engine;
import car.x.model.Forward;
import car.x.model.GE;
import car.x.model.GL;
import car.x.model.Gearbox;
import car.x.model.LE;
import car.x.model.Lamp;
import car.x.model.SwitchLight;

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
