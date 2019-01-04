var page = require('webpage').create(),
    system = require('system'),
    address;
if (system.args.length === 1) {
    console.log(system.args)
} else {
    
    //console.log(system.args)
    address = 'http://h.wandouip.com';
    page.open(address, function (status) {
        console.log(page.content)
        phantom.exit();
    });
}