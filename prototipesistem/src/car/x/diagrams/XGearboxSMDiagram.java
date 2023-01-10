package car.x.diagrams;

import hu.elte.txtuml.api.layout.Below;
import hu.elte.txtuml.api.layout.Row;
import hu.elte.txtuml.api.layout.StateMachineDiagram;
import car.x.model.Gearbox;
import car.x.model.Gearbox.Backwards;
import car.x.model.Gearbox.Forwards;
import car.x.model.Gearbox.Init;
import car.x.model.Gearbox.Neutral;

public class XGearboxSMDiagram extends StateMachineDiagram<Gearbox>{
	
	@Row({Init.class, Neutral.class})
    @Row({Forwards.class, Backwards.class})
    @Below(val = Forwards.class, from = Init.class)
    class GearLay extends Layout {}

}
