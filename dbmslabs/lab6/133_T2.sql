CREATE OR REPLACE FUNCTION register_match()
RETURNS TRIGGER 
LANGUAGE plpgsql
AS $$
DECLARE
    v_available_slots INTEGER;
BEGIN 

    SELECT available_slots INTO v_available_slots
    FROM matches
    WHERE match_id = NEW.match_id;

IF v_available_slots <= 0 THEN 
RAISE EXCEPTION 'Match is already full.';
END IF;

IF EXISTS (
        SELECT 1 
        FROM player_match 
        WHERE agent_id = NEW.agent_id 
          AND match_id = NEW.match_id
    ) THEN
        RAISE EXCEPTION 'Agent already registered for this match.';
    END IF;

UPDATE matches
SET
available_slots = available_slots - 1 
 match_status = CASE 
        WHEN (available_slots - 1) <= 0 THEN 'FULL'
        ELSE 'OPEN'
        END
    WHERE match_id = NEW.match_id;

   RETURN NEW;
END;
$$;

CREATE TRIGGER trigger_match_register
BEFORE INSERT ON player_match
FOR EACH ROW
EXECUTE FUNCTION process_match_registration();