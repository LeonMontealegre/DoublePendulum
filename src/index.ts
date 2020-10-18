import {V, Vector} from "Vector";
import {Simulation} from "utils/Simulation";

import pendulum from "./pendulum.cpp";

async function init() {
    const module = await pendulum();

    const L1 = 5;
    const L2 = 3;

    module.init(1.6, 2, 0, 0);

    const sim = new Simulation("canvas",
        () => {
            for (let i = 0; i < 3; i++)
                module.step(0.01);
        },
        (p) => {
            const a1 = module.a1() - Math.PI/2;
            const a2 = module.a2() - Math.PI/2;

            const p1 = V(0, 100);
            const p2 = Vector.fromAngle(a1).scale(L1*10).add(p1);

            p.drawLine(p1, p2);
            p.fillCirc(p2, 2);

            const p3 = p2;
            const p4 = Vector.fromAngle(a2).scale(L2*10).add(p3);

            p.drawLine(p3, p4);
            p.fillCirc(p4, 2);
        }
    );

    sim.start();
}

init();
