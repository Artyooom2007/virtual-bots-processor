unit myownbots;

interface

// ============== CONSTS =============================
const
        MAX_SIZE_X = 100;
        MAX_SIZE_Y = 100;

        GOOD_BOT = 1;
        BAD_BOT = 2;

        MAX_BOTS = 10;

        MAX_BOTS_DISTANCE = 50;
        MAX_BOTS_DISTANCE_HALF = 25;
        MAX_BOTS_GROUPS = 2;
            BOTS_SPEED = 1;

        MAX_PROJECTILES = 50;

        MAX_DEFENCE_POINTS = 25;


// ============== TYPES ===============================
        type robot = record             // BOT

                x, y:        integer;
                hp:          integer;
                status:      integer;
                plan:        array [1..4,1..3] of integer;
                action:      integer;

                planReached: boolean;

                live:        boolean;
        end;


        type projectile = record        // PROJECTILE

                x, y, angle: integer;
                realX,realY: real;
                exist:       boolean;
        end;


        type defence = record           // DEFENCE

                x, y: integer;
        end;


        type staticStrategicPoint = record  // BASE

                x, y: integer;
                radius: integer;
        end;

//================== VARS ==============================
var
        bots:  array [1..MAX_BOTS_GROUPS, 1..MAX_BOTS] of robot;                     // Bots
        projectiles: array [1..MAX_BOTS_GROUPS,1..MAX_PROJECTILES] of projectile;    // projectiles

        projectileNum: array [1..MAX_BOTS_GROUPS] of integer;

        defences: array [1..MAX_DEFENCE_POINTS] of defence;

// ============== FUNCTIONS =============================

        function degToRad (deg: integer): real;
        function radToDeg (rad: real): integer;
        function degInvertor (deg: integer): integer;
        function antipod (group: integer): integer;
        function inSquareArea (ax, ay, bx, by, radius: integer): boolean;
        function nearestEnemy (executorX, executorY, victimGroup: integer): integer;
        function nearestDefence (x, y: integer) : integer;

// ============== PROCEDURES ==============================

        procedure AllInit;
        procedure botMove(group, num, targetX, targetY: integer);
        procedure createProjectile(group,x,y,angle: integer);
        procedure projectilesCalculate;
        procedure botShoot(group, num, targetX, targetY: integer);

implementation // ================IMPLEMENTATION =================================================

uses math;

// ================== FUNCTIONS ========================

        function degToRad (deg: integer): real;
        begin
                degToRad := (deg * 3.14) / 180;
        end;


        function radToDeg (rad: real): integer;
        begin
                radToDeg := round( (rad * 180) / 3.14 );
        end;

        function degInvertor (deg: integer): integer;
        begin
                degInvertor := 360 - deg;
                end;

        function antipod (group: integer): integer;
        begin
                if group = 1 then antipod := 2;
                if group = 2 then antipod := 1;
        end;

        function inSquareArea (ax, ay, bx, by, radius: integer): boolean;
        begin
                if (bx > (ax-radius)) and (bx < (ax+radius)) and (by > (ay-radius)) and (by < (ay+radius)) then

                inSquareArea := true

                else inSquareArea := false;
        end;

        function nearestEnemy (executorX, executorY, victimGroup: integer): integer;
        var a, distance, prevDistance, victim: integer;
        begin

        victim := 0;

        prevDistance := MAX_BOTS_DISTANCE;

        for a := 1 to MAX_BOTS do
        begin
                if bots[victimGroup,a].live = true then
                begin
                        distance :=
                        abs(executorX - bots[victimGroup,a].x) +
                        abs(executorY- bots[victimGroup,a].y);
                        if distance < prevDistance then
                        begin
                                victim := a;
                                prevDistance := distance;
                        end;
                end
                else continue;
        end;

        nearestEnemy := victim;

        end;


        function nearestDefence (x, y: integer) : integer;  // To take a shit

        var a, chosenDefence, distance, prevDistance: integer;

        begin

        chosenDefence := 0;
        prevDistance := 100;    // For no reason

        for a := 1 to MAX_DEFENCE_POINTS do
        begin
                distance := abs(defences[a].x - x) + abs(defences[a].y - y);

                if distance < prevDistance then
                begin
                        chosenDefence := a;
                        prevDistance := distance;
                end;
        end;

        nearestDefence := chosenDefence;

        end;

// ===================== PROCEDURES =========================================

        procedure AllInit; //Let's spawn some BOTS
        var i, l, g, m, n, e, x, y: integer;
        begin
        randomize;

        for i := 1 to MAX_BOTS_GROUPS do
        begin
                for l := 1 to MAX_BOTS do
                begin
                        bots[i,l].x :=          random(100);
                        bots[i,l].y :=          random(100);
                        bots[i,l].hp :=         3;
                        bots[i,l].status :=     1;
                        bots[i,l].action :=     1;
                        bots[i,l].live :=       true;
                        bots[i,l].planReached:= true;
                end;

                for x := 1 to MAX_PROJECTILES do
                begin
                        projectiles[i,x].x :=    0;
                        projectiles[i,x].y :=    0;
                        projectiles[i,x].realX:= 0;
                        projectiles[i,x].realY:= 0;
                        projectiles[i,x].angle:= 0;
                        projectiles[i,x].exist:= false;
                end;

                for m := 1 to 4 do
                begin
                        for n:= 1 to 3 do
                        begin
                                        bots[i,l].plan[m,n] := 0;
                        end;
                end;
        end;


        for e := 1 to MAX_DEFENCE_POINTS do
        begin
                defences[e].x :=        random(100);
                defences[e].y :=        random(100);
        end;


        end;


        procedure botMove(group, num, targetX, targetY: integer);
        begin

        if bots[group,num].x < targetX then        bots[group,num].x := bots[group,num].x + BOTS_SPEED
        else if bots[group,num].x > targetX then   bots[group,num].x := bots[group,num].x - BOTS_SPEED;

        if bots[group,num].y < targetY then        bots[group,num].y := bots[group,num].y + BOTS_SPEED
        else if bots[group,num].y > targetY then   bots[group,num].y := bots[group,num].y - BOTS_SPEED;

        end;


        procedure createProjectile(group,x,y,angle: integer);
        begin

        projectileNum[group]:= projectileNum[group] + 1;

        projectiles[group,projectileNum[group]].x     := x;
        projectiles[group,projectileNum[group]].realX := x;
        projectiles[group,projectileNum[group]].y     := y;
        projectiles[group,projectileNum[group]].realY := y;
        projectiles[group,projectileNum[group]].angle := angle;
        projectiles[group,projectileNum[group]].exist := true;

        if projectileNum[group] = MAX_PROJECTILES then projectileNum[group] := 0; // No one will understand that because I was drunk

        end;

        procedure projectilesCalculate;
        var i,l : integer;
        begin                                   // Eh. Cycles.

        for i:= 1 to MAX_BOTS_GROUPS do
        begin
                for l:= 1 to MAX_PROJECTILES do
                begin
                        if projectiles[i,l].exist = true then
                        begin
                                projectiles[i,l].realX := projectiles[i,l].realX + cos(degToRad(projectiles[i,l].angle));
                                projectiles[i,l].realY := projectiles[i,l].realY + sin(degToRad(projectiles[i,l].angle));

                                projectiles[i,l].x := round(projectiles[i,l].realX);
                                projectiles[i,l].y := round(projectiles[i,l].realY);

                                if (projectiles[i,l].x > MAX_SIZE_X+30) or (projectiles[i,l].x < -30) then projectiles[i,l].exist := false;
                                if (projectiles[i,l].y > MAX_SIZE_Y+30) or (projectiles[i,l].y < -30) then projectiles[i,l].exist := false;
                        end;
                end;
        end;

        end;

        procedure botShoot(group, num, targetX, targetY: integer);   // I ATE HAMSTER
        begin
        // This is madness!
        createProjectile(group, bots[group,num].x, bots[group,num].y, radToDeg(arctan2((targetY - bots[group,num].y),(targetX - bots[group,num].x))) );

        end;



begin

        writeln('MyBots Ready.');

end.