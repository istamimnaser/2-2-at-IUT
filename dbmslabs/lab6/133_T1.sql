CREATE OR REPLACE PROCEDURE analyze_agent_performance(p_agent_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_agent_name VARCHAR(50);
    highest NUMERIC;
    lowest NUMERIC;
    avg NUMERIC;
    rating VARCHAR(20);
BEGIN

SELECT agent_name into v_agent_name 
FROM agents
WHERE agent_id = p_agent_id;

SELECT 
        MAX((kills + assists) - deaths),
        MIN((kills + assists) - deaths),
        AVG((kills + assists) - deaths)
INTO 
        highest, 
        lowest, 
        avg
FROM agent_performance
WHERE agent_id = p_agent_id;

IF avg >= 20 THEN
    rating := 'ELITE';
    ELSIF avg >= 15 AND avg < 20 THEN
    rating := 'PRO';
    ELSIF avg >= 10 AND avg < 15 THEN
    rating := 'ADVANCED';
    ELSE
    rating := 'ROOKIE';
    END IF;

    RAISE NOTICE 'Agent: %',agent_name;
    RAISE NOTICE 'Highest Efficiency : %',highest;
    RAISE NOTICE 'Lowest Efficiency : %',lowest;
    RAISE NOTICE 'Average Efficiency : %',avg;
    RAISE NOTICE 'Performance Rating : %',rating;
END;
$$;

CALL analyze_agent_performance(1);