dust.debugLevel = 'DEBUG';
var compiled = dust.compile("Hello {name}!", "intro");
dust.loadSource(compiled);
dust.render("intro", {name: "World"}, function(err, out) {
    if (err) {
        console.error(err);
    }
    if (out) {
        console.store(out);
    }
});
