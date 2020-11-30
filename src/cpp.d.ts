
declare module "*/pendulum.cpp" {
    export default function(): Promise<{
        init(theta0: number, theta1: number, dTheta0: number, dTheta1: number): void;
        step(h: number); void;
        a1(): number;
        a2(): number;
    }>;
}
