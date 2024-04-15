% Rules for deciding whether to go for a run based on weather conditions

% It's a nice day to go for a run if it's sunny and warm
go_for_run(sunny, warm) :-
    write('It\'s a beautiful day! Perfect for a run.').

% It's okay to go for a run if it's cloudy but warm
go_for_run(cloudy, warm) :-
    write('It\'s a bit cloudy, but still good for a run.').

% It's not ideal to go for a run if it's cold, but you can if you want
go_for_run(_, cold) :-
    write('It\'s cold out there, but if you bundle up, you can still go for a run.').

% It's not recommended to go for a run if it's raining
go_for_run(raining, _) :-
    write('It\'s raining. Better stay indoors today.').

% Main predicate for querying whether to go for a run
should_i_go_for_run(Weather, Temperature) :-
    go_for_run(Weather, Temperature),
    nl.