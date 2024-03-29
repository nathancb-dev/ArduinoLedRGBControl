var valores = {};

$(document).ready(function () {
  ajustLastItem();
  loadPage("home", "Room Control");
  $("#d_ip").html("Host: " + window.location.host);

  $(window).resize(function () {
    ajustLastItem();
  });

  $("#slide-out li").click(function () {
    let va = setInterval(ajustLastItem, 0);
    setTimeout(function () { clearInterval(va); }, 500);
  });

  $.each($.cookie(), function (i, val) {
    if (i.substring(0, 3) == "c_b") {
      if (val == "clear")
        $("#" + i.substring(2)).hide();
      else
        $("#" + i.substring(2)).show();
    }
  });

  setInterval(kappa, 100);

  function kappa() {
    $('.sidenav-overlay').each(function () {

      $b = $("main, .fixed-action-btn");

      if ($(this).is(":visible") && !$b.hasClass("side-blur"))
        $b.addClass("side-blur");
      else if (!$(this).is(":visible") && $b.hasClass("side-blur"))
        $b.removeClass("side-blur");

    });
  }

  function ajustLastItem() {
    $last = $("#slide-out li").last();
    let margin = $(window).height() - $last.position().top - $last.children().outerHeight(true) + (($last.children().outerHeight(true) - $last.children().outerHeight()) / 2);
    if (margin >= 0) $last.css("margin-top", margin);
  }
});

function loadPage(page, titleNav, callback) {
  registerValues();

  if (titleNav) $("#titleNav").html(titleNav);
  if (page) {
    page = "html/" + page;
    if (page.substring(page.length - 5) != ".htm") page += ".htm";
    $("#mainRow").load(page, loadCompleted);
  }

  function loadCompleted() {
    loadComplete(false, callback);
  }
}

function loadComplete(showSpecific, callback) {
  registerValues(true);

  $(".add").unbind('click').click(function () {
    modifyValue(this, +1);

    //if ($.cookie().c_s_saveImediato == "check") saveImmediately($(this).parent().find("input"));
  });

  $(".remove").unbind('click').click(function () {
    modifyValue(this, -1);

    //if ($.cookie().c_s_saveImediato == "check") saveImmediately($(this).parent().find("input"));
  });

  $("input[type=checkbox].isvalue.islighting").unbind('click').click(function () {
    let v = $.cookie().c_s_lightImediato;
    if (!v || v == "check") saveImmediately($(this));
  });

  if (showSpecific) showValues(showSpecific);
  else showValues();

  M.AutoInit();
  $("#loadPage").hide(); // or remove

  if (callback) setTimeout(callback, 100);

  $.each($.cookie(), function (i, val) {
    if (i.substring(0, 2) == "c_") {
      $("#" + i).children().html(val);
    }
  });

  function modifyValue(that, num) {
    $input = $(that).parent().find("input");
    $input.val(parseInt($input.val()) + num);
  }

  function saveImmediately(that) {
    let v = {};

    switch ($(that).get(0).id.substring(0, 1)) {
      case "w":
        v[$(that).get(0).id] = $(that).is(":checked");
        break;
      default:
        v[$(that).get(0).id] = $(that).get(0).value;
        break;
    }

    saveConfig(v);
  }
}

function registerValues(ifNot) {
  $.each($(".isvalue"), function (i, val) {
    let inner = $("#" + val.id).data().innerjson;

    // if que é um caralho pra entende (na vdd é fácil, porém difícil, mas fácil)
    if ((ifNot && ((!inner && !valores[val.id]) || (inner && !valores[inner]) || (valores[inner] && !valores[inner][val.id]))) || !ifNot) {
      switch (val.id.substring(0, 1)) {
        case "w":
          trataItem($("#" + val.id).is(":checked"));
          break;
        default:
          trataItem(val.value);
          break;
      }
    }

    function trataItem(value) {
      let inner = $("#" + val.id).data().innerjson;

      if (inner) {

        if (!valores[inner])
          valores[inner] = {};

        valores[inner][val.id] = value;

      } else {
        valores[val.id] = value;
      }
    }
  });
}

function showValues(specific) {
  if (!specific) specific = "";
  else specific += " ";
  $.each($(specific + ".isvalue"), function (i, val) {
    if (getValue()) {
      switch (val.id.substring(0, 1)) {
        case "w":
          if (getValue()) $("#" + val.id).attr("checked", true);
          break;
        case "s":
          val.value = getValue();
          if ($("#" + val.id).hasClass("withData")) {
            //valores[val.id] = $(val).val(); // Não sei pq, mas assim funciona (kappa)
            registerSelectLoad(val.id);
          }
          break;
        default:
          val.value = getValue();
          break;
      }
    }

    function getValue() {
      let inner = $("#" + val.id).data().innerjson;

      if (inner)
        if (valores[inner]) return valores[inner][val.id];
        else return undefined;
      else
        return valores[val.id];

    }

  });
}

function saveConfig(specific) {
  registerValues();
  M.toast({ html: "Aplicado!", classes: "rounded" });

  console.log(JSON.parse(JSON.stringify((specific ? specific : valores))));
  console.log(makeGetPost((specific ? specific : valores)));

  function makeGetPost(json) {
    if (json.length == 0) return;

    let v = "";

    for (const key in json) {
      if (key.substring(0, 7) == "fields_") continue;

      if (key.substring(0, 5) == "json_") {

        valores["fields_" + key.substring(5)].forEach(el => {
          v += "&" + el + "=" + trataValue(json[key][el]);
        });

      }
      else v += "&" + key + "=" + trataValue(json[key]);
    }

    v = v.substring(1);

    return v;

    function trataValue(value) {
      if (typeof value == "boolean") return value << 0;
      return value;
    }
  }

  function addBrToJson(json) {
    let v = JSON.stringify(json, undefined, 4);
    let c = "";
    var s = "";
    let ident = 0;
    let marksClosed = true;
    for (let i = 0; i <= v.length; i++) {
      c = v.substring(i, i + 1);
      if (c == "\"") marksClosed = !marksClosed;
      if (marksClosed) {
        switch (c) {
          case "{":
            ident += 1;
            s += c + "<br/>" + getIdent();
            break;
          case "}":
            ident -= 1;
            s += "<br/>" + getIdent() + c;
            break;
          case ",":
            s += c + "<br/>" + getIdent();
            break;
          default:
            s += c;
            break;
        }
      } else {
        s += c;
      }
    }

    return s;

    function getIdent() {
      let r = "";
      for (let i = 0; i < ident; i++) {
        r += "&nbsp;&nbsp;&nbsp;&nbsp;";
      }
      return r
    }
  }
}

function changeSaveBtn(id) {
  $i = $("#" + id).children();
  if ($i.html() == "check") {
    $i.html("clear");
    $("#" + id.substring(2)).hide();
  } else {
    $i.html("check");
    $("#" + id.substring(2)).show();
  }

  $.cookie(id, $i.html());
}

function registerSelectLoad(id) {
  loadPageSelect(id);
  $("#" + id).on("change", function () {
    loadPageSelect(id);
  });
}

function loadPageSelect(id) {

  let item = $("#" + id);
  let selected = item.find(":selected");
  let onpage = item.data().onpage;
  let nameInnerJson = item.data().nameinnerjson;
  let page = selected.data().page;
  let callback = selected.data().callback;

  if (page) $("#" + onpage).load("html/efeitosft/" + page + ".htm", loadCompleted);


  function loadCompleted() {
    if (item.hasClass("copy")) {
      valores["fields_" + id] = [];
      $.each($("#" + onpage).find(".isvalue"), function (i, val) {
        val.id += "_f" + item.data().copynumber;
        $("#" + val.id).data().innerjson = nameInnerJson;
        valores["fields_" + id].push(val.id);
      });
    }
    if (callback) window[callback]();
    loadComplete("#" + onpage);
  }
}

function estatico() {
  // load jsColor and implement onChage method
  loadJsColor().onChange = function (element, value) {
    let c = hexToRgb(value);
    let v = valores;

    $(element).val("rgb(" + c.r + "," + c.g + "," + c.b + ")");

    if ($(element).data().innerjson)
      v = valores[$(element).data().innerjson];

    v[element.id] = value;

    v["json_" + element.id] = {
      r: c.r,
      g: c.g,
      b: c.b
    }
  }
}

function hexToRgb(hex) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}
