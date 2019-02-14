var values = {};

$(document).ready(function () {
  loadPage("home");
});

function loadPage(page, titleNav, title) {
  registerValues();

  if (title) document.title = title;
  if (titleNav) $("#titleNav").html(titleNav);
  if (page) {
    page = "html/" + page;
    if (page.substring(page.length - 5) == ".html") $("#mainRow").load(page, function () { loadComplete() });
    else $("#mainRow").load(page + ".html", function () { loadComplete() });
  }

  function loadComplete() {
    $(".sidenav").sidenav();
    $(".collapsible").collapsible();
    $("#loadPage").hide(); // or remove

    $(".add").click(function () {
      modifyValue(this, +1);
    });

    $(".remove").click(function () {
      modifyValue(this, -1);
    });

    showValues();

    function kappa(that, num) {
      $input = $(that).parent().find("input");
      $input.val(parseInt($input.val()) + num);
    }
  }
}

function registerValues() {
  $.each($(".isvalue"), function (i, val) {
    values[val.id] = val.value;
  });
}

function showValues() {
  $.each($(".isvalue"), function (i, val) {
    if (values[val.id]) {
      val.value = values[val.id];
    }
  });
}