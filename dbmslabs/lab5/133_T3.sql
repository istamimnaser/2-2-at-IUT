DO$$
DECLARE 

cur CURSOR FOR SELECT agent_id, agent_name FROM agents;
    
    v_agent_id INTEGER;
    v_agent_name VARCHAR(50);
    v_avg_score NUMERIC(8,2);
    v_tier VARCHAR(50);
    v_rows_inserted INTEGER;

BEGIN 
    OPEN cur;

    LOOP
        FETCH cur INTO v_agent_id, v_agent_name;

         EXIT WHEN NOT FOUND;

         SELECT AVG(combat_score)

        INTO v_avg_score
        FROM agent_performance
        WHERE agent_id = v_agent_id;

          IF v_avg_score >= 300 THEN
            v_tier := 'Radiant Candidate';
        ELSIF v_avg_score >= 250 AND v_avg_score < 300 THEN
            v_tier := 'Immortal Candidate';
        ELSIF v_avg_score >= 200 AND v_avg_score < 250 THEN
            v_tier := 'Ascendant Candidate';
        ELSE
            v_tier := 'Needs Training';
        END IF;



        INSERT INTO promotion_review (agent_id, avg_combat_score, tier)
        VALUES (v_agent_id, v_avg_score, v_tier);
        
        GET DIAGNOSTICS v_rows_inserted = ROW_COUNT;
        
        RAISE NOTICE 'Processing: %', v_agent_name;
        RAISE NOTICE 'Average Score: %', v_avg_score;
        RAISE NOTICE 'Tier: %', v_tier;
        RAISE NOTICE 'Inserted: % row', v_rows_inserted;
        
        
    END LOOP;
    
    
    CLOSE cur_agents;
END;
$$;