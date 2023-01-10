package car.j.diagrams;

import hu.elte.txtuml.api.layout.Below;
import hu.elte.txtuml.api.layout.Row;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.j.model.Gearbox;
import car.j.model.Gearbox.Backwards;
import car.j.model.Gearbox.Forwards;
import car.j.model.Gearbox.Init;
import car.j.model.Gearbox.Neutral;

public class GearboxSMDiagrams extends StateMachineDiagram<Gearbox> {
	
	@Row({Init.class, Neutral.class})
    @Row({Forwards.class, Backwards.class})
    @Below(val = Forwards.class, from = Init.class)
    class GearLay extends Layout {}

}
